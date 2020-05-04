
// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

// Custom keycodes for modifier and layer keys
#define _LALT_A LALT_T(KC_A)
#define _LGUI_S LGUI_T(KC_S)
#define _LCTL_D LCTL_T(KC_D)
#define _LSFT_F LSFT_T(KC_F)
#define _RSFT_J RSFT_T(KC_J)
#define _RCTL_K RCTL_T(KC_K)
#define _RGUI_L RGUI_T(KC_L)
#define _LALT_SC LALT_T(KC_SCLN)

#define _TO_ADJ TT(_ADJUST)
#define _LR_BSP LT(_LOWER, KC_BSPC)
#define _LL_DEL LT(_RAISE, KC_DEL)
#define _LL_ENT LT(_RAISE, KC_ENT)
#define _LR_SPC LT(_LOWER, KC_SPC)

enum custom_keycodes {
  RGBRST = SAFE_RANGE,
  ALT_TAB,
  KC_BUZZ
};


#define QWERTY_LAYOUT \
     KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,        KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,     KC_QUOT, \
     G(KC_V),_LALT_A,_LGUI_S,_LCTL_D,_LSFT_F,KC_G,        KC_H,   _RSFT_J,_RCTL_K,_RGUI_L,_LALT_SC, KC_RPRN, \
     G(KC_C),KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,        KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,  KC_RBRC, \
                            _TO_ADJ,_LR_BSP,_LL_DEL,   _LL_ENT,_LR_SPC,KC_NO

#define LOWER_LAYOUT \
     KC_ESC, KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,     KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,  KC_MINS, \
     KC_PIPE,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,        KC_6,   KC_7,   KC_8,   KC_9,   KC_0,     KC_PPLS, \
     KC_TILD,KC_UNDS,KC_BSLS,KC_GRV,KC_LCBR,KC_RCBR,      KC_LBRC,KC_RBRC,KC_COMM,KC_DOT, KC_SLSH,  KC_PEQL, \
                             KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS

#define RAISE_LAYOUT \
     ALT_TAB,KC_NO,  KC_MS_U,KC_NO,  KC_NO,  KC_NO,       KC_NO,  KC_HOME,KC_UP,  KC_END, KC_PGUP,  KC_NO, \
     KC_NO,  KC_MS_L,KC_MS_D,KC_MS_R,KC_BTN1,KC_NO,       S(KC_DOWN),KC_LEFT,KC_DOWN,KC_RGHT,KC_PGDN,KC_NO, \
     KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,       A(KC_BSPC),A(KC_LEFT),S(A(KC_RGHT)),A(KC_RGHT),KC_NO,KC_NO, \
                             KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS
