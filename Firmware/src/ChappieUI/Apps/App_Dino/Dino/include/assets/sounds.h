#pragma once

#include <Arduino.h>

// In the end, I didn't use it...
//
// constexpr uint8_t SFX_ZAP[] PROGMEM = {
//
//     0x90, 90, 0, 3, 
//     0x90, 65, 0, 4, 
//     0x90, 50, 0, 5,
//     0x90, 80, 0, 1,
//     0x80,
//     0xf0
//
// };

uint8_t const constexpr SFX_JUMP[] PROGMEM = {

    0x90, 72, 0, 12,
    0x90, 74, 0, 12,
    0x90, 76, 0, 12,
    0x90, 78, 0, 12,
    0x90, 80, 0, 12,
    0x90, 82, 0, 12,
    0x80,
    0xf0

};

uint8_t const constexpr SFX_NEXT_LEVEL[] PROGMEM = {

    0x90, 83, 0,  75,
    0x80,
    0x90, 88, 0, 175,
    0x80,
    0xf0

};

uint8_t const constexpr SFX_GAME_OVER[] PROGMEM = {

    0x90, 60, 0,  50, 
    0x90, 50, 0, 100, 
    0x90, 30, 0, 200,
    0x80,
    0xf0

};

uint8_t const constexpr THEME_LOOP[] PROGMEM = {

    0x90, 57,
    0x91, 57,
    0x92, 33, 0, 52,
    0x80,
    0x81, 0, 101,
    0x82, 0, 3,
    0x90, 59,
    0x91, 59,
    0x92, 35, 0, 52,
    0x80,
    0x81, 0, 101,
    0x82, 0, 3,
    0x90, 61,
    0x91, 61,
    0x92, 37, 0, 52,
    0x80,
    0x81, 0, 101,
    0x82, 0, 3,
    0x90, 62,
    0x91, 62,
    0x92, 38, 0, 154,
    0x82, 0, 161,
    0x93, 30,
    0x92, 33, 0, 105,
    0x80,
    0x81, 0, 49,
    0x82, 0, 3,
    0x90, 61,
    0x91, 61, 0, 49,
    0x80,
    0x81, 0, 3,
    0x90, 62,
    0x91, 62, 0, 49,
    0x80,
    0x81, 0, 3,
    0x90, 64,
    0x91, 64,
    0x83, 0, 49,
    0x80,
    0x81, 0, 3,
    0x92, 38,
    0x90, 66,
    0x91, 66, 0, 154,
    0x82, 0, 161,
    0x93, 30,
    0x92, 33, 0, 105,
    0x80,
    0x81, 0, 49,
    0x82, 0, 3,
    0x90, 64,
    0x91, 64, 0, 49,
    0x80,
    0x81, 0, 3,
    0x90, 66,
    0x91, 66, 0, 49,
    0x80,
    0x81, 0, 3,
    0x90, 67,
    0x91, 67,
    0x83, 0, 49,
    0x80,
    0x81, 0, 3,
    0x92, 38,
    0x90, 69,
    0x91, 69, 0, 52,
    0x80,
    0x81, 0, 101,
    0x82, 0, 3,
    0x90, 68,
    0x91, 68, 0, 52,
    0x80,
    0x81, 0, 105,
    0x92, 33,
    0x93, 30,
    0x90, 67,
    0x91, 67, 0, 52,
    0x80,
    0x81, 0, 101,
    0x82, 0, 3,
    0x90, 66,
    0x91, 66, 0, 52,
    0x80,
    0x81, 0, 52,
    0x83, 0, 52,
    0x90, 64,
    0x91, 64,
    0x92, 38, 0, 52,
    0x80,
    0x81, 0, 101,
    0x82, 0, 3,
    0x90, 62,
    0x91, 62, 0, 52,
    0x80,
    0x81, 0, 105,
    0x92, 33,
    0x93, 30,
    0x90, 61,
    0x91, 61, 0, 52,
    0x80,
    0x81, 0, 101,
    0x82, 0, 3,
    0x90, 59,
    0x91, 59, 0, 52,
    0x80,
    0x81, 0, 52,
    0x83, 0, 52,
    0x90, 64,
    0x91, 60,
    0x92, 36, 0, 154,
    0x82, 0, 108,
    0x80,
    0x81, 0, 52,
    0x92, 31,
    0x93, 30,
    0x90, 62,
    0x91, 59, 0, 101,
    0x80,
    0x81, 0, 3,
    0x90, 64,
    0x91, 60, 0, 49,
    0x82, 0, 52,
    0x80,
    0x81, 0, 3,
    0x90, 62,
    0x91, 59, 0, 52,
    0x83, 0, 49,
    0x80,
    0x81, 0, 3,
    0x92, 36,
    0x90, 60,
    0x91, 57, 0, 154,
    0x82, 0, 108,
    0x80,
    0x81, 0, 52,
    0x92, 31,
    0x93, 30,
    0x90, 59,
    0x91, 55, 0, 154,
    0x82, 0, 108,
    0x80,
    0x81,
    0x83, 0, 52,
    0x92, 38,
    0x90, 66,
    0x91, 62, 0, 52,
    0x80,
    0x81, 0, 101,
    0x82, 0, 3,
    0x90, 66,
    0x91, 62, 0, 52,
    0x80,
    0x81, 0, 105,
    0x92, 33,
    0x93, 30,
    0x90, 64,
    0x91, 61, 0, 52,
    0x80,
    0x81, 0, 101,
    0x82, 0, 3,
    0x90, 64,
    0x91, 61, 0, 52,
    0x80,
    0x81, 0, 52,
    0x83, 0, 52,
    0x90, 62,
    0x91, 57,
    0x92, 38, 0, 52,
    0x80,
    0x81, 0, 101,
    0x82, 0, 3,
    0xe0

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