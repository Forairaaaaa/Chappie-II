#pragma once

// #include <ESPboy.h>
// #include <ESPboyPlaytune.h>
// #include <FixedPoints.h>
// #include <FixedPointsCommon.h>
#include "Dino.h"
#include "assets/sprites.h"
// #include <LovyanGFX.hpp>
#include "../../../../../ChappieBsp/Chappie.h"
#include "../FixedPointsArduino/src/FixedPoints.h"
#include "../FixedPointsArduino/src/FixedPointsCommon.h"

#define TFT_WIDTH   128
#define TFT_HEIGHT  128


class Game {

    public:

        void begin(CHAPPIE* device);
        void loop();

    private:

        static uint8_t  constexpr _DINO_X          = 16;
        static uint8_t  constexpr _BASELINE        = TFT_HEIGHT - GROUND_SIZE;
        static uint8_t  constexpr _GROUND_REPEAT   = 1 + TFT_WIDTH / GROUND_SIZE;
        static SQ15x16  constexpr _DISTANCE_FACTOR = .14f;
        static uint8_t  constexpr _MAX_CUBE_NUMBER = 10;
        static SQ7x8    constexpr _MIN_GAP         = 2.75f * ICE_CUBE_SIZE;
        static uint8_t  constexpr _STAR_NUMBER     = 60;
        static uint8_t  constexpr _STAR_COLORS     = 6;

        // static uint16_t const constexpr _STAR_COLOR[] = { 0x0273, 0x0339, 0x34df, 0x9e7f, 0x34df, 0x0339 };
        // static uint16_t _STAR_COLOR[] = { 0x0273, 0x0339, 0x34df, 0x9e7f, 0x34df, 0x0339 };

        // Initially, I wanted to handle highscore backup with LittleFS,
        // but interference with ESPboyPlaytune caused me to give up.
        // I finally chose to rely on ESP_EEPROM, which is lighter, simpler,
        // and has no issues with the combined use of ESPboyPlaytune.
        //
        // static char constexpr _DATA_FILE[] = "/dino.txt";
        // bool     _has_littlefs;
        // uint16_t _highscore;

        static uint8_t    constexpr _EEPROM_ADDR       = 0;
        static char const constexpr _EEPROM_DATA_TAG[] = "DINO";

        struct EEPROM_Data {
            char     tag[5];
            uint16_t highscore;
        };

        EEPROM_Data _backup_data;

        enum class TextAlign : uint8_t {
            LEFT,
            CENTER,
            RIGHT
        };

        LGFX_Sprite    *_framebuffer;
        // ESPboyPlaytune *_sfx;

        Dino *_dino;

        struct Cube {
            SQ15x16 x;
            uint8_t floor;
            bool    cracked;
            bool    solid;
        };

        Cube _cube[_MAX_CUBE_NUMBER];

        struct Star {
            SQ15x16 x;
            SQ15x16 y;
            uint8_t color_index;
        };

        Star _star[_STAR_NUMBER];

        uint8_t _cubes;
        uint8_t _last_cube_index;
        SQ7x8   _last_cube_x;
        uint8_t _clusters;
        uint8_t _remaining_clusters;

        enum class Stage : uint8_t {
            SPLASH,
            INIT,
            PLAY,
            STOP,
            GAME_OVER
        };

        Stage   _stage;
        uint8_t _level;
        SQ15x16 _speed;
        SQ15x16 _scroll_x;
        SQ15x16 _distance;

        void _splash();
        void _init();
        void _play();
        void _stop();
        void _gameOver();
        void _restart();

        void _reset();
        void _spawnCubes();
        void _spawnCube(uint8_t const x, uint8_t const floor, bool const cracked = false);
        void _twinkleStars();
        void _scroll();
        void _checkCollisions();
        void _nextLevel();

        inline uint16_t const _score() const;
        
        void _loadHighScore();
        void _saveHighScore();

        void _initDraw();
        void _drawSplash();
        void _drawPlay();
        void _drawGameOver();

        void _drawString(char const * const str, uint8_t x, uint8_t const y, uint16_t const color = 0xffff, TextAlign const align = TextAlign::LEFT) const;

};

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