#include QMK_KEYBOARD_H
#if __has_include("keymap.h")
#    include "keymap.h"
#endif

enum custom_keycodes {
    AP_GLOB = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case AP_GLOB:
            host_consumer_send(record->event.pressed ? 0x029D : 0);
            return false;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_66_ansi(QK_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_VOLU, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_VOLD, KC_LGUI, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_LCTL, AP_GLOB, KC_LGUI, KC_SPC, KC_LALT, MO(1), KC_LCTL, KC_LEFT, KC_DOWN, KC_RGHT),
    [1] = LAYOUT_66_ansi(KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, KC_VOLU, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MPRV, KC_MPLY, KC_MNXT, KC_NO, KC_MUTE, KC_VOLD, KC_NO, KC_NO, MO(2), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PGUP, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, MO(1), KC_NO, KC_HOME, KC_PGDN, KC_END),
    [2] = LAYOUT_66_ansi(BL_STEP, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, KC_NO, KC_NO, KC_NO, KC_NO, UG_TOGG, UG_VALU, KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, UG_VALD, KC_NO, KC_NO, MO(2), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, UG_SATU, KC_NO, KC_NO, KC_NO, UG_NEXT, KC_NO, MO(1), KC_NO, UG_HUED, UG_SATD, UG_HUEU)
};




#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif // OTHER_KEYMAP_C

