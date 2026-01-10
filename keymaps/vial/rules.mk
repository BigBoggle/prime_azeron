# Joystick
JOYSTICK_ENABLE = yes
JOYSTICK_DRIVER = analog

# OLED
OLED_ENABLE = yes

BOOTMAGIC_ENABLE = yes


# Debug
CONSOLE_ENABLE = yes
JOYSTICK_DEBUG = yes
MATRIX_DEBUG = yes

SRC += common/joystick.c common/oled.c


# Vial
VIA_ENABLE = yes
VIAL_ENABLE = yes
