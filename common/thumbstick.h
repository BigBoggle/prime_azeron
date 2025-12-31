#pragma once

// TODO: Adapt to my needs

#include "quantum.h"
#include "state.h"
#include <stdint.h>

int16_t xPos;
int16_t yPos;

typedef struct {
  uint16_t angle;
  uint16_t distance;
} thumbstick_polar_position_t;

typedef struct {
  bool w;
  bool a;
  bool s;
  bool d;
  bool shift;
} wasd_state_t;

thumbstick_polar_position_t thumbstick_polar_position;

wasd_state_t wasd_state;
wasd_state_t last_wasd_state;

void init_wasd_state(void);

thumbstick_polar_position_t get_thumbstick_polar_position(int16_t x, int16_t y);

bool update_keystate(uint16_t angle_from, uint16_t angle_to, uint16_t angle);

void update_keycode(uint16_t keycode, bool keystate, bool last_keystate);

void thumbstick(controller_state_t controller_state);
