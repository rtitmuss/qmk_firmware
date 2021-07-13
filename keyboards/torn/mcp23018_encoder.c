/*
 * Copyright 2020 Richard Titmuss <richard.titmuss@gmail.com>
 * Copyright 2018 Jack Humbert <jack.humb@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "mcp23018.h"

#ifndef ENCODER_RESOLUTION
#    define ENCODER_RESOLUTION 4
#endif

#define ENCODER_CLOCKWISE true
#define ENCODER_COUNTER_CLOCKWISE false

static int8_t encoder_LUT[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};

static uint8_t encoder_state  = 0;
static int8_t  encoder_pulses = 0;

static bool encoder_read_state(uint8_t *state) {
    mcp23018_pin_t    pins;
    mcp23018_status_t status = mcp23018_readGpio(&pins);
    if (status == 0) {
        *state = ((pins & SECONDARY_ENCODER_PAD_A) > 0) << 0 | ((pins & SECONDARY_ENCODER_PAD_B) > 0) << 1;
        return true;
    }
    return false;
}

static void encoder_update(int8_t index, uint8_t state) {
    encoder_pulses += encoder_LUT[state & 0xF];
    if (encoder_pulses >= ENCODER_RESOLUTION) {
        encoder_update_kb(index, ENCODER_CLOCKWISE);
    }
    if (encoder_pulses <= -ENCODER_RESOLUTION) {  // direction is arbitrary here, but this clockwise
        encoder_update_kb(index, ENCODER_COUNTER_CLOCKWISE);
    }
    encoder_pulses %= ENCODER_RESOLUTION;
}

/**
 * Read the secondary encoder over i2c
 */
void mcp23018_encoder_read(void) {
    uint8_t state;
    if (encoder_read_state(&state)) {
        encoder_state <<= 2;
        encoder_state |= state;
        encoder_update(1, encoder_state);
    }
}

/**
 * Initialize the secondary encoder over i2c
 */
void mcp23018_encoder_init(void) { encoder_read_state(&encoder_state); }
