// #include "Game.h"
// #include "assets/font.h"
// #include "assets/sounds.h"
#include "../include/Game.h"
#include "../include/assets/font.h"
#include "../include/assets/sounds.h"

// Initially, I wanted to handle highscore backup with LittleFS,
// but interference with ESPboyPlaytune caused me to give up.
// I finally chose to rely on ESP_EEPROM, which is lighter, simpler,
// and has no issues with the combined use of ESPboyPlaytune.
//
// #include <LittleFS.h>
// #include <ESP_EEPROM.h>

static uint16_t _STAR_COLOR[] = { 0x0273, 0x0339, 0x34df, 0x9e7f, 0x34df, 0x0339 };
static CHAPPIE* _device;

boolean outEn() { return true; }

void Game::begin(CHAPPIE* device) {
    _device = device;

    _loadHighScore();

    _stage = Stage::SPLASH;

    _framebuffer = new LGFX_Sprite(&device->Lcd);
    _framebuffer->setPsram(true);
    _framebuffer->createSprite(TFT_WIDTH, TFT_HEIGHT);

    // _sfx = new ESPboyPlaytune(outEn);
    // _sfx->setSynth(EPT_SYNTH_SQUARE, 128);
    // _sfx->initChannel(0);

    // espboy.pixel.setBrightness(0x20);

    _dino = new Dino(_DINO_X, _BASELINE);

    Star *s;
    for (uint8_t i = 0; i < _STAR_NUMBER; ++i) {
        s              = &_star[i];
        s->x           = random(TFT_WIDTH);
        s->y           = random(_BASELINE);
        s->color_index = random(_STAR_COLORS);
    }

    // _sfx->playScore(THEME_LOOP);

}

void Game::loop() {

    _twinkleStars();

    switch (_stage) {

        case Stage::SPLASH:    _splash(); break;
        case Stage::INIT:      _init();   break;
        case Stage::PLAY:      _play();   break;
        case Stage::STOP:      _stop();   break;
        case Stage::GAME_OVER: _gameOver();
        
    }

    // _framebuffer->pushSprite(0, 0);
    _framebuffer->pushRotateZoom(0, 1.875, 1.875);

}

void Game::_splash() {

    // if (espboy.button.pressed(Button::ACT)) _stage = Stage::INIT;
    if (_device->Tp.isTouched()) {
        while (_device->Tp.isTouched()) { delay(10); }
        _stage = Stage::INIT;
    }

    _dino->wait();
    _drawSplash();

}

void Game::_init() {

    // _sfx->stopScore();
    _reset();
    _drawPlay();

}

void Game::_play() {

    // if (espboy.button.pressed(Button::ACT) && !_dino->jumping()) {
        // _dino->jump();
        // _sfx->playScore(SFX_JUMP);
    // }

    if (_device->Tp.isTouched() && !_dino->jumping()) {
        _dino->jump();
    }

    _spawnCubes();
    _scroll();
    _dino->update(_speed);
    _checkCollisions();
    _drawPlay();

}

void Game::_stop() {

    _stage = Stage::GAME_OVER;

    _saveHighScore();
    _drawGameOver();
    // _sfx->playScore(SFX_GAME_OVER);
    // espboy.pixel.flash(Color::hsv2rgb(0), 50, 3, 200);

}

void Game::_gameOver() {

    // if (espboy.button.pressed(Button::ACT)) {
    //     _restart();
    //     _sfx->playScore(THEME_LOOP);
    // }

    if (_device->Tp.isTouched()) {
        while (_device->Tp.isTouched()) { delay(10); }
        _restart();
    }

    _drawGameOver();

}

void Game::_restart() {

    _dino->reset();
    _stage = Stage::SPLASH;

}

void Game::_reset() {

    _cubes           = 0;
    _last_cube_index = 0;
    _last_cube_x     = TFT_WIDTH - _MIN_GAP;

    for (uint8_t i = 0; i < _MAX_CUBE_NUMBER; ++i) _cube[i].solid = false;

    _remaining_clusters = _clusters = 10;

    _level    = 1;
    _speed    = 1.5f;
    _distance = 0;
    _scroll_x = 0;
    
    _stage = Stage::PLAY;

}

void Game::_spawnCubes() {
    
    uint8_t bound;

    switch (_level) {

        case 1:
        case 2: bound = 50; break;
        case 3:
        case 4: bound = 40; break;
        case 5:
        case 6: bound = 30; break;

        default: bound = 20;

    }

    if (random(bound)) return;
        
    Cube *c = &_cube[_last_cube_index];

    if ((c->solid && c->x + _speed * _MIN_GAP > TFT_WIDTH) || _dino->y() > _BASELINE) return;
    
    switch (_level) {

        case 1:
        case 2: bound = 1; break;
        case 3: bound = 2; break;
        case 4: bound = 4; break;
        case 5: bound = 5; break;
        
        default: bound = 6;

    }

    uint8_t r = random(bound);

    switch (r) {

        case 0:
            _spawnCube(TFT_WIDTH, 0);
            break;

        case 1:
            _spawnCube(TFT_WIDTH, 0, true);
            _spawnCube(TFT_WIDTH, 1);
            break;

        case 2:
            _spawnCube(TFT_WIDTH, 0);
            _spawnCube(TFT_WIDTH + ICE_CUBE_SIZE, 0, true);
            _spawnCube(TFT_WIDTH + ICE_CUBE_SIZE, 1);
            break;

        case 3:
            _spawnCube(TFT_WIDTH, 0, true);
            _spawnCube(TFT_WIDTH, 1);
            _spawnCube(TFT_WIDTH + ICE_CUBE_SIZE, 0);
            break;

        case 4:
            _spawnCube(TFT_WIDTH, 0);
            _spawnCube(TFT_WIDTH + 2 * ICE_CUBE_SIZE, 0);
            break;

        case 5:
            _spawnCube(TFT_WIDTH, 0);
            _spawnCube(TFT_WIDTH +     ICE_CUBE_SIZE, 0, true);
            _spawnCube(TFT_WIDTH +     ICE_CUBE_SIZE, 1);
            _spawnCube(TFT_WIDTH + 2 * ICE_CUBE_SIZE, 0);

    }

    // espboy.pixel.flash(Color::hsv2rgb(210), 50);

    if (--_remaining_clusters == 0) _nextLevel();

}

void Game::_spawnCube(uint8_t const x, uint8_t const floor, bool const cracked) {

    if (_cubes < _MAX_CUBE_NUMBER) {

        _last_cube_index++; if (_last_cube_index == _MAX_CUBE_NUMBER) _last_cube_index = 0;

        Cube *c = &_cube[_last_cube_index];

        c->x       = x;
        c->floor   = floor;
        c->cracked = cracked;
        c->solid   = true;

        _cubes++;

    }

}

void Game::_twinkleStars() {

    Star *s;
    for (uint8_t i = 0; i < _STAR_NUMBER; ++i) {
        if (((millis() >> 6) & 0x1) && random(10) == 0) {
            s = &_star[i];
            s->color_index++; if (s->color_index == _STAR_COLORS) s->color_index = 0;
        }
    }

}

void Game::_scroll() {

    Star *s;
    for (uint8_t i = 0; i < _STAR_NUMBER; ++i) {
        s = &_star[i];
        s->x -= _speed * .05f;
        if (s->x < 0) {
            s->x = TFT_WIDTH - 1;
            s->y = random(_BASELINE);
        }
    }

    if (_cubes) {

        Cube *c;
        for (uint8_t i = 0; i < _MAX_CUBE_NUMBER; ++i) {
            c = &_cube[i];
            if (c->solid) {
                c->x -= _speed;
                if (c->x < - ICE_CUBE_SIZE) {
                    c->solid = false;
                    _cubes--;
                }
            }
        }

    }

    _distance += _speed * _DISTANCE_FACTOR;
    _scroll_x += _speed;
    
    if (_scroll_x > GROUND_SIZE) _scroll_x -= GROUND_SIZE;

}

void Game::_checkCollisions() {

    Cube *c;
    for (uint8_t i = 0; i < _MAX_CUBE_NUMBER; ++i) {
        c = &_cube[i];
        if (c->solid) {
            if (_dino->collidingWith(static_cast<int8_t>(c->x), _BASELINE - (c->floor + 1) * ICE_CUBE_SIZE, ICE_CUBE_SIZE)) {
                _stage = Stage::STOP;
            }
        }
    }

}

void Game::_nextLevel() {

    _level++;
    _speed += .25f;

    switch (_level) {

        case 2: _clusters = 10; break;
        case 3: _clusters = 20; break;
        case 4:
        case 5: _clusters = 30; break;

        default: _clusters = 40;

    }

    _remaining_clusters = _clusters;

    // _sfx->playScore(SFX_NEXT_LEVEL);

}

inline uint16_t const Game::_score() const { return static_cast<uint16_t>(_distance); }

void Game::_loadHighScore() {

    // EEPROM.begin(sizeof(EEPROM_Data));

    // if (EEPROM.percentUsed() >= 0) {
    //     EEPROM.get(_EEPROM_ADDR, _backup_data);
    //     if (strcmp(_backup_data.tag, _EEPROM_DATA_TAG) == 0) return;
    // }

    // strncpy((char*)&_backup_data.tag, _EEPROM_DATA_TAG, sizeof(_EEPROM_DATA_TAG));
    _backup_data.highscore = 0;

    // Initially, I wanted to handle highscore backup with LittleFS,
    // but interference with ESPboyPlaytune caused me to give up.
    // I finally chose to rely on ESP_EEPROM, which is lighter, simpler,
    // and has no issues with the combined use of ESPboyPlaytune.
    //
    // _highscore = 0;
    //
    // if ((_has_littlefs = LittleFS.begin())) {
    //     File file = LittleFS.open(_DATA_FILE, "r");
    //     if (file) file.read((uint8_t*)&_highscore, 2);
    // }

}

void Game::_saveHighScore() {

    uint16_t const score = _score();

    if (score > _backup_data.highscore) {

        _backup_data.highscore = score;

        // EEPROM.put(_EEPROM_ADDR, _backup_data);
        // EEPROM.commit();

        // Initially, I wanted to handle highscore backup with LittleFS,
        // but interference with ESPboyPlaytune caused me to give up.
        // I finally chose to rely on ESP_EEPROM, which is lighter, simpler,
        // and has no issues with the combined use of ESPboyPlaytune.
        //
        // if (_has_littlefs) {
        //     File file = LittleFS.open(_DATA_FILE, "w");
        //     if (file) file.write((uint8_t const *)&_highscore, 2);
        // }

    }

}

void Game::_initDraw() {

    _framebuffer->clear();

    for (uint8_t i = 0; i < _GROUND_REPEAT; ++i) {
        _framebuffer->pushImage(
            static_cast<int8_t>(i * GROUND_SIZE - _scroll_x),
            _BASELINE,
            GROUND_SIZE,
            GROUND_SIZE,
            GROUND
        );
    }

    Star s;
    for (uint8_t i = 0; i < _STAR_NUMBER; ++i) {
        s = _star[i];
        _framebuffer->drawPixel(
            static_cast<int8_t>(s.x),
            static_cast<int8_t>(s.y),
            _STAR_COLOR[s.color_index]
        );
    }

}

void Game::_drawSplash() {

    _initDraw();

    uint8_t y = ((TFT_HEIGHT >> 1) - SPLASH_HEIGHT) >> 1;

    _framebuffer->pushImage(
        (TFT_WIDTH - SPLASH_WIDTH) >> 1,
        y,
        SPLASH_WIDTH,
        SPLASH_HEIGHT,
        SPLASH,
        TRANS_COLOR
    );

    _drawString("TOUCH SCREEN", TFT_WIDTH >> 1, y + SPLASH_HEIGHT + 8, 0xffff, TextAlign::CENTER);

    _dino->draw(_framebuffer);

    _framebuffer->pushImage(
        TFT_WIDTH - _DINO_X - ICE_CUBE_SIZE,
        _BASELINE - ICE_CUBE_SIZE,
        ICE_CUBE_SIZE,
        ICE_CUBE_SIZE,
        ICE_CUBE,
        TRANS_COLOR
    );

}

void Game::_drawPlay() {

    _initDraw();

    Cube *c;
    for (uint8_t i = 0; i < _MAX_CUBE_NUMBER; ++i) {
       c = &_cube[i];
        if (c->solid) {
            _framebuffer->pushImage(
                static_cast<int8_t>(c->x),
                _BASELINE - (c->floor + 1) * ICE_CUBE_SIZE,
                ICE_CUBE_SIZE,
                ICE_CUBE_SIZE,
                ICE_CUBE + (c->cracked ? ICE_CUBE_FRAME_SIZE : 0),
                TRANS_COLOR
            );
        }
    }

    if (_stage != Stage::GAME_OVER || (millis() >> 7) & 0x1) {
        _dino->draw(_framebuffer);
    }

    char score[6]; snprintf(score, 6, "%5u", _score());

    _drawString(score, TFT_WIDTH - 2, 2, 0xffff, TextAlign::RIGHT);

    for (uint8_t i = 1; i < _level; ++i) {
        _framebuffer->pushImage(
            42 + i * (FLAG_WIDTH + 1),
            5 - (FLAG_HEIGHT >> 1),
            FLAG_WIDTH,
            FLAG_HEIGHT,
            FLAG,
            TRANS_COLOR
        );
    }

    _framebuffer->drawRect(0, 3, 40, 5, 0x9b20);
    _framebuffer->drawFastHLine(2, 5, 36 * (_clusters + 1 - _remaining_clusters) / _clusters, 0xfdc6);

}

void Game::_drawGameOver() {

    _drawPlay();

    uint8_t const x = TFT_WIDTH >> 1;
    uint8_t       y = TFT_WIDTH / 6;

    if ((millis() >> 8) & 0x1) {
        _drawString("GAME OVER", x, y, 0xf800, TextAlign::CENTER);
    }

    char highscore[6]; snprintf(highscore, 6, "%u", _backup_data.highscore);

    _drawString("HIGH SCORE", x, y += FONT_SIZE + 6, 0xffff, TextAlign::CENTER);
    _drawString(highscore, x, y + FONT_SIZE + 6, 0xf800, TextAlign::CENTER);

}

void Game::_drawString(char const * const str, uint8_t x, uint8_t const y, uint16_t const color, TextAlign const align) const {

    uint8_t const n = strlen(str);

    uint8_t k;
    char c;

    switch (align) {
        case TextAlign::CENTER: x -= (n * (FONT_SIZE + 1) - 1) >> 1;  break;
        case TextAlign::RIGHT:  x -= n * (FONT_SIZE + 1) - 1;         break;
        default:;
    }

    for (uint8_t i = 0; i < n; ++i) {

        c = str[i];
        if (c == 0x20) { x += FONT_SIZE + 1; continue; }
        if (c == 0x2d) k = 36;
        else if (c == 0x3a) k = 37;
        else if (c > 0x2f && c < 0x3a) k = c - 0x30;
        else k = 10 + c - 0x41;

        _framebuffer->drawBitmap(
            x,
            y,
            FONT + k * FONT_SIZE,
            FONT_SIZE,
            FONT_SIZE,
            color
        );

        x += FONT_SIZE + 1;

    }

}

/**
 * ----------------------------------------------------------------------------
 * Dino Game
 * ----------------------------------------------------------------------------
 * Copyright (c) 2022 Stéphane Calderoni (https://github.com/m1cr0lab)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 * ----------------------------------------------------------------------------
 */