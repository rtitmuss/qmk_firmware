#include QMK_KEYBOARD_H
#include <rtitmuss.h>

/****************************************************************************************************
*
* Keymap: Default Layer in Qwerty
*
* ,-------------------------------------------------------------------------------------------------------------------.
* | Esc    |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F8  |  F9  |  F10 |  F12 | PSCR | SLCK | PAUS |  FN0 |  BOOT  |
* |--------+------+------+------+------+------+---------------------------+------+------+------+------+------+--------|
* | =+     |  1!  |  2@  |  3#  |  4$  |  5%  |                           |  6^  |  7&  |  8*  |  9(  |  0)  | -_     |
* |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
* | Tab    |   Q  |   W  |   E  |   R  |   T  |                           |   Y  |   U  |   I  |   O  |   P  | \|     |
* |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
* | Caps   |   A  |   S  |   D  |   F  |   G  |                           |   H  |   J  |   K  |   L  |  ;:  | '"     |
* |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
* | Shift  |   Z  |   X  |   C  |   V  |   B  |                           |   N  |   M  |  ,.  |  .>  |  /?  | Shift  |
* `--------+------+------+------+------+-------                           `------+------+------+------+------+--------'
*          | `~   | INS  | Left | Right|                                         | Up   | Down |  [{  |  ]}  |
*          `---------------------------'                                         `---------------------------'
*                                        ,-------------.         ,-------------.
*                                        | Ctrl | Alt  |         | Gui  | Ctrl |
*                                 ,------|------|------|         |------+------+------.
*                                 |      |      | Home |         | PgUp |      |      |
*                                 | BkSp | Del  |------|         |------|Return| Space|
*                                 |      |      | End  |         | PgDn |      |      |
*                                 `--------------------'         `--------------------'
*/

static uint8_t keycount = 0;

#define LAYOUT_CORNE( \
     K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, \
     K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, \
     K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, \
     K31, K32, K33, K34, K35, K36 \
  ) \
  LAYOUT( \
    RESET,  KC_BUZZ,KC_BUZZ,KC_BUZZ,KC_BUZZ,KC_BUZZ,KC_BUZZ,KC_BUZZ,KC_BUZZ,\
    KC_BUZZ,KC_BUZZ,KC_BUZZ,KC_BUZZ,KC_BUZZ,KC_BUZZ,\
    K01,    K02,    K03,    K04,    K05,    K06, \
    K11,    K12,    K13,    K14,    K15,    K16, \
    K21,    K22,    K23,    K24,    K25,    K26, \
    KC_BUZZ,KC_BUZZ,KC_BUZZ,KC_BUZZ,\
    KC_BUZZ,KC_BUZZ,KC_BUZZ,K32,    K33,    KC_BUZZ,\
    \
    KC_BUZZ,KC_BUZZ,KC_BUZZ,KC_BUZZ,KC_BUZZ,KC_BUZZ,KC_BUZZ,KC_BUZZ,KC_BUZZ,\
	KC_BUZZ,KC_BUZZ,KC_BUZZ,KC_BUZZ,KC_BUZZ,KC_BUZZ,\
	K07,    K08,    K09,    K0A,    K0B,    K0C, \
	K17,    K18,    K19,    K1A,    K1B,    K1C, \
	K27,    K28,    K29,    K2A,    K2B,    K2C, \
	KC_BUZZ,KC_BUZZ,KC_BUZZ,KC_BUZZ,\
    KC_BUZZ,KC_BUZZ,KC_BUZZ,KC_BUZZ,K34,    K35 \
 )

#define LAYOUT_CORNE_wrapper(...)       LAYOUT_CORNE(__VA_ARGS__)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_CORNE_wrapper(QWERTY_LAYOUT),
  [_LOWER] = LAYOUT_CORNE_wrapper(LOWER_LAYOUT),
  [_RAISE] = LAYOUT_CORNE_wrapper(RAISE_LAYOUT)
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    keycount++;
    PORTD = (PORTD & 0xBF) | ((keycount & 1) << 6);
    PORTC = (PORTC & 0x7F) | ((keycount & 2) << 6);
  }

  switch (keycode) {
    case KC_BUZZ:
      if (record->event.pressed) {
        PORTE = (PORTE & 0xBF) | ~0x40;
        _delay_ms(100);
        PORTE = (PORTE & 0xBF) | 0x40;
      }
      break;
  }
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {

    switch (get_highest_layer(state)) {
    case _RAISE:
        PORTD = (PORTD & 0x6F) | ~0x80;
        break;
    case _LOWER:
        PORTD = (PORTD & 0x6F) | ~0x10;
        break;
    default:
        PORTD = (PORTD & 0x6F) | 0x90;
    }
  return state;
}

void led_set_user(uint8_t usb_led) {

}
