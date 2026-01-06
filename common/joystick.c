#include "joystick.h"
#include "action.h"
#include "analog.h"
#include "keycodes.h"
#include "matrix.h"
#include "print.h"
#include <stdint.h>
#include <stdlib.h>

// NOTE: This stick firmware only works well with the physical 8 way restrictor piece
// https://www.thingiverse.com/thing:5326847

#ifdef JOYSTICK_ENABLE

// Read from analogReadPin
#define _CENTER_X 783
#define _CENTER_Y 748

#define _DEADZONE 100

#define _Y_DOWN_THRESHOLD (_CENTER_Y + _DEADZONE)
#define _Y_UP_THRESHOLD (_CENTER_Y - _DEADZONE + 10)

#define _X_RIGHT_THRESHOLD (_CENTER_X + _DEADZONE + 10)
#define _X_LEFT_THRESHOLD (_CENTER_X - _DEADZONE)

//clang-format on
// -------------------- Joystick Config --------------------
int16_t xPos = 0;
int16_t yPos = 0;

// Held flags
bool yDownHeld = false;
bool yUpHeld = false;
bool xRightHeld = false;
bool xLeftHeld = false;

// Axis inversion
bool invertX = false; // true if left/right is reversed
bool invertY = true;  // true if up/down is reversed

bool wasdMode = true; //

// Deadzone for diagonal filtering
#define _DIAGONAL_DEADZONE (_DEADZONE * 2)

// -------------------- Scan Loop --------------------
void matrix_scan_user(void)
{
    int16_t rawX = analogReadPin(ANALOG_AXIS_PIN_X);
    int16_t rawY = analogReadPin(ANALOG_AXIS_PIN_Y);

    // Apply inversion
    int16_t x = invertX ? 2 * _CENTER_X - rawX : rawX;
    int16_t y = invertY ? 2 * _CENTER_Y - rawY : rawY;

    if (!wasdMode)
        return;

    // Offsets from center
    int16_t dx = x - _CENTER_X;
    int16_t dy = y - _CENTER_Y;

    // Apply base deadzone
    if (abs(dx) < _DEADZONE)
        dx = 0;
    if (abs(dy) < _DEADZONE)
        dy = 0;

    // Neutral
    if (dx == 0 && dy == 0)
    {
        unregister_code(KC_W);
        unregister_code(KC_S);
        unregister_code(KC_A);
        unregister_code(KC_D);
        xLeftHeld = xRightHeld = yUpHeld = yDownHeld = false;
        return;
    }

    // Directional Logic
    if (abs(dy) >= abs(dx))
    {
        // Vertical dominates
        if (dy > 0)
        { // S
            if (!yDownHeld)
            {
                register_code(KC_S);
                yDownHeld = true;
            }
            if (yUpHeld)
            {
                unregister_code(KC_W);
                yUpHeld = false;
            }
        }
        else
        { // W
            if (!yUpHeld)
            {
                register_code(KC_W);
                yUpHeld = true;
            }
            if (yDownHeld)
            {
                unregister_code(KC_S);
                yDownHeld = false;
            }
        }

        if (dx > 0)
        { // D
            if (abs(dx) > _DIAGONAL_DEADZONE && !xRightHeld)
            {
                register_code(KC_D);
                xRightHeld = true;
            }
            if (abs(dx) <= _DIAGONAL_DEADZONE && xRightHeld)
            {
                unregister_code(KC_D);
                xRightHeld = false;
            }
        }
        else if (dx < 0)
        { // A
            if (abs(dx) > _DIAGONAL_DEADZONE && !xLeftHeld)
            {
                register_code(KC_A);
                xLeftHeld = true;
            }
            if (abs(dx) <= _DIAGONAL_DEADZONE && xLeftHeld)
            {
                unregister_code(KC_A);
                xLeftHeld = false;
            }
        }
    }
    else
    {
        if (dx > 0)
        { // D
            if (!xRightHeld)
            {
                register_code(KC_D);
                xRightHeld = true;
            }
            if (xLeftHeld)
            {
                unregister_code(KC_A);
                xLeftHeld = false;
            }
        }
        else
        { // A
            if (!xLeftHeld)
            {
                register_code(KC_A);
                xLeftHeld = true;
            }
            if (xRightHeld)
            {
                unregister_code(KC_D);
                xRightHeld = false;
            }
        }

        if (dy > 0)
        { // S
            if (abs(dy) > _DIAGONAL_DEADZONE && !yDownHeld)
            {
                register_code(KC_S);
                yDownHeld = true;
            }
            if (abs(dy) <= _DIAGONAL_DEADZONE && yDownHeld)
            {
                unregister_code(KC_S);
                yDownHeld = false;
            }
        }
        else if (dy < 0)
        { // W
            if (abs(dy) > _DIAGONAL_DEADZONE && !yUpHeld)
            {
                register_code(KC_W);
                yUpHeld = true;
            }
            if (abs(dy) <= _DIAGONAL_DEADZONE && yUpHeld)
            {
                unregister_code(KC_W);
                yUpHeld = false;
            }
        }
    }

#ifdef CONSOLE_ENABLE
    static uint16_t last_print = 0;
    if (timer_elapsed(last_print) >= 100)
    {
        last_print = timer_read();
        uprintf("X:%4d Y:%4d dx:%4d dy:%4d\n", x, y, dx, dy);
    }
#endif
}

// Assign Joystick inputs to struct
joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {JOYSTICK_AXIS_IN(ANALOG_AXIS_PIN_X, 0, _CENTER_X, 1023),
                                                        JOYSTICK_AXIS_IN(ANALOG_AXIS_PIN_Y, 0, _CENTER_Y, 1023)};

#endif /* JOYSTICK_ENABLE */
