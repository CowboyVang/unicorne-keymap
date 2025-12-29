# Pure QMK keymap build rules (no Vial)

# QMK Features
COMBO_ENABLE = yes
AUTO_SHIFT_ENABLE = yes
CAPS_WORD_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
SPACE_CADET_ENABLE = yes
REPEAT_KEY_ENABLE = yes

# Custom Features
SRC += features/select_word.c
