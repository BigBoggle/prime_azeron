#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // TODO: Make better keymaps
    [0] =
        // clang-format off
        LAYOUT(KC_A, KC_B, KC_C, KC_D, 
               KC_F, KC_G, KC_H, KC_I, 
               KC_F, KC_G, KC_H, KC_I, 
               KC_F, KC_G, KC_H, KC_I, 
               KC_F, KC_G, KC_H, KC_I, 
               KC_F, KC_G,  
              )

};


joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    JOYSTICK_AXIS_IN(GP28, 900, 575, 285),
    JOYSTICK_AXIS_IN(GP29, 900, 575, 285),
};

// clang-format on
//
//
