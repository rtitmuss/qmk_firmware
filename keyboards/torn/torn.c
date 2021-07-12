/*
 * Copyright 2020 Richard Titmuss <richard.titmuss@gmail.com>
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
#include "torn.h"
#include "i2c_master.h"
#include "mcp23018.h"

static uint8_t led_state[3] = {1, 1, 1};

static const uint8_t mcp23018_iodir[] = MCP23018_IODIR;
static const uint8_t mcp23018_gppu[]  = MCP23018_GPPU;
static const uint8_t mcp23018_gpio[]  = MCP23018_GPIO;

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    i2c_init();

    matrix_init_user();
}

void matrix_scan_kb(void) {
    // put your looping keyboard code here
    // runs every cycle (a lot)
    if (mcp23018_reset_required()) {
        msp23018_init(mcp23018_iodir, mcp23018_gppu, mcp23018_gpio);
        secondary_encoder_init();
        // torn_set_led(2, 1);
    }

    matrix_scan_user();
    secondary_encoder_read();
}

void torn_set_led(uint8_t led, bool state) {
    led_state[led] = !state;

    // toggle leds by setting the pin direction
    uint8_t iodir = 0b11111000 | led_state[0] << 2 | led_state[1] << 1 | led_state[2];
    mcp23018_writeReg(IODIRB, &iodir, 1);
}

// clang-format off
const char PROGMEM bongocat_logo[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xf8, 0x98, 0x98, 0x98, 0x98, 0x98, 0x18, 0x18, 0x98,
  0x98, 0x98, 0x98, 0x98, 0xf8, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x80, 0xc0, 0x60, 0x30, 0x30, 0x18, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98,
  0x18, 0x30, 0x30, 0x60, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xf8, 0xf8, 0x18, 0x18, 0x98, 0x98, 0x98, 0x98, 0x98, 0x98, 0x18, 0x38,
  0x70, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xf8, 0xf8, 0x38, 0x70, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xf8, 0xf8, 0x18, 0x18, 0xf8, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0xff, 0xff, 0x00, 0x00, 0xff,
  0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xf8, 0xfe, 0x07, 0x01, 0xf0, 0xfc, 0x0e, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x03, 0x03, 0x0e, 0xfc, 0xf0, 0x01, 0x07, 0xfe, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xc1, 0xc1, 0xc1, 0x63, 0x3f, 0x1c,
  0xc0, 0xe1, 0x7f, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xff, 0xff, 0x00, 0x00, 0xf8, 0xf1, 0xe3, 0xc7, 0x8e, 0x1c, 0x38, 0x70, 0xe0, 0xc0, 0x80, 0x00,
  0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xff,
  0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0f, 0x3f, 0x70, 0xc0, 0x87, 0x1f, 0x38, 0x60, 0x60, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
  0x60, 0x60, 0x38, 0x1f, 0x87, 0xc0, 0xf0, 0x7f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0xfe, 0xfe, 0x0e, 0x3c, 0x78, 0xe2, 0xc7, 0x1f,
  0x39, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x01, 0x03, 0x07, 0x0e, 0x1c, 0x38, 0x71, 0xe3, 0xc7,
  0x8f, 0x1f, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0c, 0x0c, 0x0f,
  0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x06, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
  0x0c, 0x06, 0x06, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0c, 0x0c, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0f,
  0x0c, 0x0c, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0f, 0x0f, 0x0c, 0x0c, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x03, 0x07, 0x0e, 0x0c, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// clang-format on
