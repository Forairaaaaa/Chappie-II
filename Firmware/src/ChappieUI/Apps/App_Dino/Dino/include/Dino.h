#pragma once

// #include <ESPboy.h>
// #include <FixedPoints.h>
// #include <FixedPointsCommon.h>
#include <LovyanGFX.hpp>
#include "../FixedPointsArduino/src/FixedPoints.h"
#include "../FixedPointsArduino/src/FixedPointsCommon.h"

class Dino {

    public:

        Dino(uint8_t const x, uint8_t const baseline);

        SQ7x8 const y()       const;
        bool  const jumping() const;

        void reset();
        void jump();
        void wait();

        bool const collidingWith(int8_t const x, uint8_t const y, uint8_t const size) const;

        void update(SQ15x16 const speed);
        void draw(LGFX_Sprite * const framebuffer) const;

    private:

        static uint8_t constexpr _JUMP    = 4;
        static SQ7x8   constexpr _GRAVITY = .2f;

        UQ8x8   const _x;
        SQ7x8         _y;
        SQ7x8         _vy;
        uint8_t const _baseline;
        
        bool    _jumping;
        uint8_t _frame;

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