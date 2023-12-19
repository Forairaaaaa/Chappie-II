// #include "Dino.h"
// #include "assets/sprites.h"
#include "../include/Dino.h"
#include "../include/assets/sprites.h"

Dino::Dino(uint8_t const x, uint8_t const baseline)
: _x(x)
, _y(baseline - DINO_HEIGHT)
, _vy(0)
, _baseline(baseline)
, _jumping(false)
, _frame(0) {}

SQ7x8 const Dino::y()       const { return _y;       }
bool  const Dino::jumping() const { return _jumping; }

void Dino::reset() {
    _y       = _baseline - DINO_HEIGHT;
    _vy      = 0;
    _jumping = false;
    _frame   = 0;
}

void Dino::jump() {
    _vy      = -_JUMP;
    _jumping = true;
}

void Dino::wait() {

    static uint8_t flip = 0;

    if (((millis() >> 7) & 0x1) == flip) {
        _frame++; if (_frame == DINO_WAIT_FRAMES) _frame = 0;
        flip = !flip;
    }
    
}

bool const Dino::collidingWith(int8_t const x, uint8_t const y, uint8_t const size) const {

    return _x + 2               < x + size &&
           _x + DINO_WIDTH  - 2 > x        &&
           _y                   < y + size &&
           _y + DINO_HEIGHT - 1 > y;

}

void Dino::update(SQ15x16 const speed) {

    _y  += _vy;
    _vy += _GRAVITY;

    if (_y + DINO_HEIGHT > _baseline) {
        _y       = _baseline - DINO_HEIGHT;
        _vy      = 0;
        _jumping = false;
    }

    static uint8_t counter = 0;
    static uint8_t start_frame = DINO_WAIT_FRAMES;
    static uint8_t end_frame = start_frame + DINO_RUN_FRAMES;

    if (++counter * speed > 6) {
        counter = 0;
        _frame++; if (_frame < end_frame) return;
        _frame = start_frame;
    }

}

void Dino::draw(LGFX_Sprite * const framebuffer) const {

    framebuffer->pushImage(
        static_cast<uint8_t>(_x),
        static_cast<int8_t>(_y),
        DINO_WIDTH,
        DINO_HEIGHT,
        DINO + (_jumping ? DINO_JUMP_FRAME : _frame) * DINO_FRAME_SIZE,
        TRANS_COLOR
    );

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