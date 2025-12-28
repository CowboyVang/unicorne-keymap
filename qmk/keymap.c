/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H

// =============================================================================
// Layer Definitions
// =============================================================================
enum layers {
    _BASE,  // Layer 0: Colemak-DH
    _NAV,   // Layer 1: Navigation & Raycast
    _SYM    // Layer 2: Numbers & Symbols
};

// =============================================================================
// Custom Keycodes
// =============================================================================
#define OSM_SYM LT(_SYM, KC_NO)  // Hold for layer, tap handled by tap dance alternative

// =============================================================================
// Combos
// =============================================================================
// Left Hand - Vertical
const uint16_t PROGMEM combo_esc[] = {KC_W, KC_R, COMBO_END};          // W + R = Escape (Ring vertical)
const uint16_t PROGMEM combo_tab[] = {KC_F, KC_S, COMBO_END};          // F + S = Tab (Middle vertical)
// Left Hand - Horizontal
const uint16_t PROGMEM combo_del[] = {KC_F, KC_P, COMBO_END};          // F + P = Delete (Top row)
const uint16_t PROGMEM combo_undo[] = {KC_X, KC_C, COMBO_END};         // X + C = Cmd+Z (Bottom row)
const uint16_t PROGMEM combo_redo[] = {KC_C, KC_D, COMBO_END};         // C + D = Cmd+Y (Bottom row)
const uint16_t PROGMEM combo_paste_plain[] = {KC_D, KC_V, COMBO_END};  // D + V = Cmd+Shift+V (Bottom row)
// Left Hand - Diagonal
const uint16_t PROGMEM combo_bspc[] = {KC_F, KC_T, COMBO_END};         // F + T = Backspace (Top middle + Home index)
// Right Hand - Vertical
const uint16_t PROGMEM combo_pipe[] = {KC_U, KC_E, COMBO_END};         // U + E = Pipe (Middle vertical)
const uint16_t PROGMEM combo_backtick[] = {KC_Y, KC_I, COMBO_END};     // Y + I = Backtick (Ring vertical)
const uint16_t PROGMEM combo_capsword[] = {KC_L, KC_N, COMBO_END};     // L + N = Caps Word (Middle vertical)
// Right Hand - Diagonal
const uint16_t PROGMEM combo_shift_enter[] = {KC_N, KC_U, COMBO_END};  // N + U = Shift+Enter (Home index + mid)

combo_t key_combos[COMBO_COUNT] = {
    // Left Hand
    COMBO(combo_esc, KC_ESC),              // W + R = Escape
    COMBO(combo_tab, KC_TAB),              // F + S = Tab
    COMBO(combo_del, KC_DEL),              // F + P = Delete
    COMBO(combo_undo, G(KC_Z)),            // X + C = Undo
    COMBO(combo_redo, G(KC_Y)),            // C + D = Redo
    COMBO(combo_paste_plain, G(S(KC_V))),  // D + V = Paste without format
    COMBO(combo_bspc, KC_BSPC),            // F + T = Backspace
    // Right Hand
    COMBO(combo_pipe, S(KC_BSLS)),         // U + E = Pipe |
    COMBO(combo_backtick, KC_GRV),         // Y + I = Backtick `
    COMBO(combo_capsword, CW_TOGG),        // L + N = Caps Word Toggle
    COMBO(combo_shift_enter, S(KC_ENT)),   // N + U = Shift+Enter
};

// =============================================================================
// Key Overrides (Bracket Pairs)
// =============================================================================
// Shift + [ = ]
const key_override_t lbrc_override = ko_make_basic(MOD_MASK_SHIFT, KC_LBRC, KC_RBRC);
// Shift + ( = )
const key_override_t lprn_override = ko_make_basic(MOD_MASK_SHIFT, KC_LPRN, KC_RPRN);
// Shift + { = }
const key_override_t lcbr_override = ko_make_basic(MOD_MASK_SHIFT, KC_LCBR, KC_RCBR);

const key_override_t *key_overrides[] = {
    &lbrc_override,
    &lprn_override,
    &lcbr_override,
    NULL
};

// =============================================================================
// Auto Shift Custom Whitelist
// =============================================================================
// Only these keys will auto-shift when held:
//   ; -> :    ' -> "    / -> ?    - -> _    = -> +
// Excludes: alpha, numeric, brackets (Key Override conflict), comma, period
bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case KC_SCLN:  // ; -> :
        case KC_QUOT:  // ' -> "
        case KC_SLSH:  // / -> ?
        case KC_MINS:  // - -> _
        case KC_EQL:   // = -> +
            return true;
        default:
            return false;
    }
}

// =============================================================================
// Keymaps
// =============================================================================
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
     * Layer 0: Base (Colemak-DH)
     * Pure Space. Smart Shift/Layer Thumb.
     *
     * ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐   ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
     * │ KC_TAB  │  KC_Q   │  KC_W   │  KC_F   │  KC_P   │  KC_B   │   │  KC_J   │  KC_L   │  KC_U   │  KC_Y   │ KC_SCLN │ KC_MINS │
     * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
     * │ KC_ESC  │  KC_A   │  KC_R   │  KC_S   │  KC_T   │  KC_G   │   │  KC_M   │  KC_N   │  KC_E   │  KC_I   │  KC_O   │ KC_QUOT │
     * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
     * │ KC_LSFT │  KC_Z   │  KC_X   │  KC_C   │  KC_D   │  KC_V   │   │  KC_K   │  KC_H   │ KC_COMM │ KC_DOT  │ KC_SLSH │ KC_BSLS │
     * └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┤   ├─────────┼─────────┼─────────┴─────────┴─────────┴─────────┘
     *                               │MO(_NAV) │ KC_SPC  │ KC_LGUI │   │RSFT_T(E)│LT(SYM,B)│ OSM(SFT)│
     *                               └─────────┴─────────┴─────────┘   └─────────┴─────────┴─────────┘
     */
    [_BASE] = LAYOUT_split_3x6_3(
    //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
       LCTL_T(KC_TAB), KC_Q, KC_W,   KC_F,     KC_P,     KC_B,                          KC_J,     KC_L,     KC_U,     KC_Y,     KC_SCLN,  KC_BSLS,
    //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
       LALT_T(KC_ESC), KC_A, KC_R,   KC_S,     KC_T,     KC_G,                          KC_M,     KC_N,     KC_E,     KC_I,     KC_O,     KC_QUOT,
    //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
       SC_LSPO,  KC_Z,     KC_X,     KC_C,     KC_D,     KC_V,                          KC_K,     KC_H,     HYPR_T(KC_COMM), MEH_T(KC_DOT), KC_SLSH, SC_RSPC,
    //└─────────┴─────────┴─────────┼─────────┼─────────┼─────────┤                    ├─────────┼─────────┼─────────┴─────────┴─────────┴─────────┘
                                     LT(_NAV,KC_MINS), KC_SPC, LGUI_T(KC_EQL),          RSFT_T(KC_ENT), LT(_SYM,KC_BSPC), RALT_T(KC_NO)
    //                              └─────────┴─────────┴─────────┘                    └─────────┴─────────┴─────────┘
    ),

    /*
     * Layer 1: Navigation & Raycast
     * Left: Raycast F-keys with modifiers. Right: Navigation (vim-style).
     *
     * ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐   ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐
     * │ S(KC_F15)│ S(KC_F16)│ S(KC_F17)│ S(KC_F18)│ S(KC_F19)│ S(KC_F20)│   │ KC_PGUP  │ KC_HOME  │  KC_INS  │  KC_END  │  KC_DEL  │ KC_VOLU  │
     * ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤   ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
     * │  KC_F15  │LCTL_T(16)│LALT_T(17)│LSFT_T(18)│LGUI_T(19)│  KC_F20  │   │ KC_PGDN  │ KC_LEFT  │ KC_DOWN  │  KC_UP   │ KC_RGHT  │ KC_VOLD  │
     * ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤   ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
     * │G(S(F15)) │G(S(F16)) │G(S(F17)) │G(S(F18)) │G(S(F19)) │G(S(F20)) │   │ XXXXXXX  │ KC_MINS  │ KC_MINS  │ KC_PLUS  │  KC_EQL  │ KC_MUTE  │
     * └──────────┴──────────┴──────────┼──────────┼──────────┼──────────┤   ├──────────┼──────────┼──────────┴──────────┴──────────┴──────────┘
     *                                  │ _______  │ _______  │ _______  │   │ KC_LSFT  │ KC_BSPC  │ _______  │
     *                                  └──────────┴──────────┴──────────┘   └──────────┴──────────┴──────────┘
     */
    [_NAV] = LAYOUT_split_3x6_3(
    //┌────────────────┬────────────────┬────────────────┬────────────────┬────────────────┬────────────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
       S(KC_F15),       S(KC_F16),       S(KC_F17),       S(KC_F18),       S(KC_F19),       S(KC_F20),                            KC_PGUP,  KC_HOME,  KC_INS,   KC_END,   KC_DEL,   KC_VOLU,
    //├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤                    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
       KC_F15,          LCTL_T(KC_F16),  LALT_T(KC_F17),  LSFT_T(KC_F18),  LGUI_T(KC_F19),  KC_F20,                               KC_PGDN,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_VOLD,
    //├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤                    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
       G(S(KC_F15)),    G(S(KC_F16)),    G(S(KC_F17)),    G(S(KC_F18)),    G(S(KC_F19)),    G(S(KC_F20)),                         XXXXXXX,  KC_MINS,  S(KC_MINS), KC_PLUS, KC_EQL,   KC_MUTE,
    //└────────────────┴────────────────┴────────────────┼────────────────┼────────────────┼────────────────┤                    ├─────────┼─────────┼─────────┴─────────┴─────────┴─────────┘
                                                          _______,         _______,         _______,                              KC_LSFT,  KC_BSPC,  KC_DEL
    //                                                   └────────────────┴────────────────┴────────────────┘                    └─────────┴─────────┴─────────┘
    ),

    /*
     * Layer 2: Numbers (Left) & Symbols (Right)
     * Left: Numpad layout. Right: Math & Logic symbols.
     *
     * ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐   ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐
     * │  TG(2)   │ KC_SLSH  │  KC_P7   │  KC_P8   │  KC_P9   │ KC_MINS  │   │ KC_PERC  │ KC_LABK  │ KC_RABK  │ KC_EXLM  │ KC_QUES  │ KC_GRV   │
     * ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤   ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
     * │ TO(_BASE)│ KC_ASTR  │  KC_P4   │  KC_P5   │  KC_P6   │  KC_P0   │   │ KC_PIPE  │ KC_LBRC  │ KC_LPRN  │ KC_LCBR  │ KC_EQL   │ KC_BSLS  │
     * ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤   ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
     * │ XXXXXXX  │ XXXXXXX  │  KC_P1   │  KC_P2   │  KC_P3   │ KC_EQL   │   │ KC_TILD  │ KC_MINS  │ KC_ASTR  │ KC_SLSH  │ KC_DLR   │ KC_CIRC  │
     * └──────────┴──────────┴──────────┼──────────┼──────────┼──────────┤   ├──────────┼──────────┼──────────┴──────────┴──────────┴──────────┘
     *                                  │ KC_PDOT  │G(KC_SPC) │ KC_LSFT  │   │  KC_ENT  │ KC_BSPC  │ _______  │
     *                                  └──────────┴──────────┴──────────┘   └──────────┴──────────┴──────────┘
     */
    [_SYM] = LAYOUT_split_3x6_3(
    //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
       TG(_SYM), KC_SLSH,  KC_P7,    KC_P8,    KC_P9,    KC_MINS,                       KC_PERC,  KC_LABK,  KC_RABK,  KC_EXLM,  KC_QUES,  KC_GRV,
    //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
       TO(_BASE),KC_ASTR,  KC_P4,    KC_P5,    KC_P6,    KC_P0,                         KC_PIPE,  KC_LBRC,  KC_LPRN,  KC_LCBR,  KC_EQL,   KC_BSLS,
    //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
       XXXXXXX,  XXXXXXX,  KC_P1,    KC_P2,    KC_P3,    KC_EQL,                        KC_TILD,  KC_MINS,  KC_ASTR,  KC_SLSH,  KC_DLR,   KC_CIRC,
    //└─────────┴─────────┴─────────┼─────────┼─────────┼─────────┤                    ├─────────┼─────────┼─────────┴─────────┴─────────┴─────────┘
                                     KC_PDOT,  G(KC_SPC),KC_LSFT,                       KC_ENT,   KC_BSPC,  _______
    //                              └─────────┴─────────┴─────────┘                    └─────────┴─────────┴─────────┘
    )
};
