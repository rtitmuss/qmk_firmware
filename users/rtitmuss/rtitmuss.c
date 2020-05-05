#include QMK_KEYBOARD_H
#include <rtitmuss.h>

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;
uint8_t chordcode;

char tohex(uint8_t n) {
  if (n > 9)
    return 'A' + n - 10;
  return '0' + n;
}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LGUI);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;

    case KC_HEX_128:
    case KC_HEX_64:
    case KC_HEX_32:
    case KC_HEX_16:
    case KC_HEX_8:
    case KC_HEX_4:
    case KC_HEX_2:
    case KC_HEX_1: {
      uint8_t chordbit = 1 << (keycode - KC_HEX_1);

      if (record->event.pressed) {
        chordcode |= chordbit;
      } else {
        chordcode &= ~chordbit;
      }

#ifdef OLED_DRIVER_ENABLE
      char buf[5] = "00  ";
      buf[0] = tohex(chordcode >> 4);
      buf[1] = tohex(chordcode & 0xF);
      buf[3] = chordcode;
      oled_write(buf, false);
#endif
      return false;
    }

    case KC_HEX_ENTER:
      if (record->event.pressed) {
        send_char(chordcode);
      }
      return false;
  }

  return process_record_keymap(keycode, record);
}

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LGUI);
      is_alt_tab_active = false;
    }
  }
}
