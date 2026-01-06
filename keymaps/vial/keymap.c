#include "keycodes.h"
#include QMK_KEYBOARD_H

enum custom_keycodes
{
    J_UP,
    J_DOWN,
    J_LEFT,
    J_RIGHT,
};

// -------------------- Keymap --------------------
// TODO: Create Different Keymap layers
// TF2
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(

        // clang-format off
                 KC_ESC, KC_COMMA, KC_TRNS, KC_TRNS,
                 KC_1, KC_2, KC_3, KC_4,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_LSFT, KC_TRNS, KC_TRNS, KC_SPC,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_F, KC_E, KC_SPC)};

