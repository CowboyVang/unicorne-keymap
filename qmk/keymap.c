/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H
#include "features/select_word.h"

// =============================================================================
// Layer Definitions
// =============================================================================
enum layers {
    _BASE,  // Layer 0: Colemak-DH
    _NAV,   // Layer 1: Navigation & System Orchestrator
    _SYM    // Layer 2: Numbers & Symbols
};

// =============================================================================
// Custom Keycodes
// =============================================================================
enum custom_keycodes {
    SELWORD = SAFE_RANGE,
    SELWBAK,
    SELLINE,
};

// Select Word keycode (required by select_word.c)
uint16_t SELECT_WORD_KEYCODE = SELWORD;

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
const uint16_t PROGMEM combo_paste[] = {KC_S, KC_D, COMBO_END};        // S + D = Cmd+V Paste (Home middle + Bottom index)
// Right Hand - Vertical
const uint16_t PROGMEM combo_pipe[] = {KC_U, KC_E, COMBO_END};         // U + E = Pipe (Middle vertical)
const uint16_t PROGMEM combo_backtick[] = {KC_Y, KC_I, COMBO_END};     // Y + I = Backtick (Ring vertical)
const uint16_t PROGMEM combo_apostrophe[] = {KC_L, KC_N, COMBO_END};   // L + N = Apostrophe (Index vertical)
// Right Hand - Horizontal
const uint16_t PROGMEM combo_slash[] = {KC_L, KC_U, COMBO_END};        // L + U = Slash (Top row)
const uint16_t PROGMEM combo_exclam[] = {KC_U, KC_Y, COMBO_END};       // U + Y = Exclamation (Top row)
// Right Hand - Diagonal
const uint16_t PROGMEM combo_shift_enter[] = {KC_N, KC_U, COMBO_END};  // N + U = Shift+Enter (Home index + mid)
// Left Hand - Vertical (additional)
const uint16_t PROGMEM combo_capsword[] = {KC_P, KC_T, COMBO_END};     // P + T = Caps Word (Index vertical)
const uint16_t PROGMEM combo_minimize[] = {KC_W, KC_F, COMBO_END};     // W + F = Cmd+M (Minimize)

combo_t key_combos[COMBO_COUNT] = {
    // Left Hand
    COMBO(combo_esc, KC_ESC),              // W + R = Escape
    COMBO(combo_tab, KC_TAB),              // F + S = Tab
    COMBO(combo_del, KC_DEL),              // F + P = Delete
    COMBO(combo_undo, G(KC_Z)),            // X + C = Undo
    COMBO(combo_redo, G(KC_Y)),            // C + D = Redo
    COMBO(combo_paste_plain, G(S(KC_V))),  // D + V = Paste without format (Cmd+Shift+V)
    COMBO(combo_bspc, KC_BSPC),            // F + T = Backspace
    COMBO(combo_paste, G(KC_V)),           // S + D = Paste (Cmd+V)
    COMBO(combo_capsword, CW_TOGG),        // P + T = Caps Word Toggle
    // Right Hand
    COMBO(combo_pipe, S(KC_BSLS)),         // U + E = Pipe |
    COMBO(combo_backtick, KC_GRV),         // Y + I = Backtick `
    COMBO(combo_apostrophe, KC_QUOT),      // L + N = Apostrophe '
    COMBO(combo_slash, KC_SLSH),           // L + U = Slash /
    COMBO(combo_exclam, KC_EXLM),          // U + Y = Exclamation !
    COMBO(combo_shift_enter, S(KC_ENT)),   // N + U = Shift+Enter
    COMBO(combo_minimize, G(KC_M)),        // W + F = Minimize
};

// =============================================================================
// Key Overrides (Bracket Pairs + Angle Brackets)
// =============================================================================
// Shift + [ = ]
const key_override_t lbrc_override = ko_make_basic(MOD_MASK_SHIFT, KC_LBRC, KC_RBRC);
// Shift + ( = )
const key_override_t lprn_override = ko_make_basic(MOD_MASK_SHIFT, KC_LPRN, KC_RPRN);
// Shift + { = }
const key_override_t lcbr_override = ko_make_basic(MOD_MASK_SHIFT, KC_LCBR, KC_RCBR);
// Shift + < = >
const key_override_t labk_override = ko_make_basic(MOD_MASK_SHIFT, KC_LABK, KC_RABK);

const key_override_t *key_overrides[] = {
    &lbrc_override,
    &lprn_override,
    &lcbr_override,
    &labk_override,
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
// Process Record User (Custom Keycodes & Select Word)
// =============================================================================
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Handle Select Word (forward selection)
    if (!process_select_word(keycode, record)) { return false; }

    switch (keycode) {
        case SELWBAK:  // Select word backward
            if (record->event.pressed) {
                select_word_register('B');
            } else {
                select_word_unregister();
            }
            return false;
        case SELLINE:  // Select line
            if (record->event.pressed) {
                select_word_register('L');
            } else {
                select_word_unregister();
            }
            return false;
    }
    return true;
}

// =============================================================================
// Keymaps
// =============================================================================
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
     * Layer 0: Base (Colemak-DH)
     * Pure Space. Smart Shift/Layer Thumb. Repeat Key on outer right.
     *
     * ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐   ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
     * │ KC_TAB  │  KC_Q   │  KC_W   │  KC_F   │  KC_P   │  KC_B   │   │  KC_J   │  KC_L   │  KC_U   │  KC_Y   │ KC_SCLN │ KC_BSLS │
     * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
     * │ KC_ESC  │  KC_A   │  KC_R   │  KC_S   │  KC_T   │  KC_G   │   │  KC_M   │  KC_N   │  KC_E   │  KC_I   │  KC_O   │ KC_QUOT │
     * ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
     * │SC_LSPO  │  KC_Z   │  KC_X   │  KC_C   │  KC_D   │  KC_V   │   │  KC_K   │  KC_H   │ KC_COMM │ KC_DOT  │ KC_SLSH │SC_RSPC  │
     * └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┤   ├─────────┼─────────┼─────────┴─────────┴─────────┴─────────┘
     *                               │GUI_T(=) │ KC_SPC  │LT(NAV,-)│   │RSFT_T(E)│LT(SYM,B)│ QK_REP  │
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
                                     LGUI_T(KC_EQL), KC_SPC, LT(_NAV,KC_MINS),          RSFT_T(KC_ENT), LT(_SYM,KC_BSPC), QK_REP
    //                              └─────────┴─────────┴─────────┘                    └─────────┴─────────┴─────────┘
    ),

    /*
     * Layer 1: Navigation & System Orchestrator
     * Left: System Orchestrator F-keys with modifiers. Right: Navigation (vim-style) + Select Word.
     *
     * ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐   ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐
     * │ S(KC_F15)│ S(KC_F16)│ S(KC_F17)│ S(KC_F18)│ S(KC_F19)│ S(KC_F20)│   │ KC_PGUP  │ SELWBAK  │ SELWORD  │ SELLINE  │  KC_END  │ KC_VOLU  │
     * ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤   ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
     * │  KC_F15  │LCTL_T(16)│LALT_T(17)│LSFT_T(18)│LGUI_T(19)│  KC_F20  │   │ KC_PGDN  │ KC_LEFT  │ KC_DOWN  │  KC_UP   │ KC_RGHT  │ KC_VOLD  │
     * ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤   ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
     * │G(S(F15)) │G(S(F16)) │G(S(F17)) │G(S(F18)) │G(S(F19)) │G(S(F20)) │   │ KC_HOME  │ KC_MINS  │ KC_UNDS  │  KC_EQL  │ KC_PLUS  │ KC_MUTE  │
     * └──────────┴──────────┴──────────┼──────────┼──────────┼──────────┤   ├──────────┼──────────┼──────────┴──────────┴──────────┴──────────┘
     *                                  │ _______  │ _______  │ _______  │   │ KC_LSFT  │ KC_BSPC  │ QK_AREP  │
     *                                  └──────────┴──────────┴──────────┘   └──────────┴──────────┴──────────┘
     */
    [_NAV] = LAYOUT_split_3x6_3(
    //┌────────────────┬────────────────┬────────────────┬────────────────┬────────────────┬────────────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
       S(KC_F15),       S(KC_F16),       S(KC_F17),       S(KC_F18),       S(KC_F19),       S(KC_F20),                            KC_PGUP,  SELWBAK,  SELWORD,  SELLINE,  KC_END,   KC_VOLU,
    //├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤                    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
       KC_F15,          LCTL_T(KC_F16),  LALT_T(KC_F17),  LSFT_T(KC_F18),  LGUI_T(KC_F19),  KC_F20,                               KC_PGDN,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_VOLD,
    //├────────────────┼────────────────┼────────────────┼────────────────┼────────────────┼────────────────┤                    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
       G(S(KC_F15)),    G(S(KC_F16)),    G(S(KC_F17)),    G(S(KC_F18)),    G(S(KC_F19)),    G(S(KC_F20)),                         KC_HOME,  KC_MINS,  KC_UNDS,  KC_EQL,   KC_PLUS,  KC_MUTE,
    //└────────────────┴────────────────┴────────────────┼────────────────┼────────────────┼────────────────┤                    ├─────────┼─────────┼─────────┴─────────┴─────────┴─────────┘
                                                          _______,         _______,         _______,                              KC_LSFT,  KC_BSPC,  QK_AREP
    //                                                   └────────────────┴────────────────┴────────────────┘                    └─────────┴─────────┴─────────┘
    ),

    /*
     * Layer 2: Numbers (Left) & Symbols (Right)
     * Left: Normal numbers (not numpad). Right: Symbols optimized for programming.
     * DF(_SYM) sets default layer, DF(_BASE) returns. Key Override: Shift+< = >
     *
     * ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐   ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐
     * │ DF(_SYM) │ KC_SLSH  │  KC_7    │  KC_8    │  KC_9    │ KC_MINS  │   │ KC_CIRC  │  KC_AT   │ KC_ASTR  │ KC_HASH  │ KC_AMPR  │ KC_DLR   │
     * ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤   ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
     * │DF(_BASE) │ KC_ASTR  │  KC_4    │  KC_5    │  KC_6    │  KC_0    │   │ KC_LABK  │ KC_LBRC  │ KC_LCBR  │ KC_LPRN  │ KC_GRV   │ KC_QUOT  │
     * ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤   ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
     * │ XXXXXXX  │ XXXXXXX  │  KC_1    │  KC_2    │  KC_3    │ KC_EQL   │   │ KC_TILD  │ KC_MINS  │ KC_UNDS  │ KC_EQL   │ KC_PLUS  │ KC_PERC  │
     * └──────────┴──────────┴──────────┼──────────┼──────────┼──────────┤   ├──────────┼──────────┼──────────┴──────────┴──────────┴──────────┘
     *                                  │ KC_DOT   │G(KC_SPC) │ KC_LSFT  │   │  KC_ENT  │ KC_BSPC  │ _______  │
     *                                  └──────────┴──────────┴──────────┘   └──────────┴──────────┴──────────┘
     */
    [_SYM] = LAYOUT_split_3x6_3(
    //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
       DF(_SYM), KC_SLSH,  KC_7,     KC_8,     KC_9,     KC_MINS,                       KC_CIRC,  KC_AT,    KC_ASTR,  KC_HASH,  KC_AMPR,  KC_DLR,
    //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
       DF(_BASE),KC_ASTR,  KC_4,     KC_5,     KC_6,     KC_0,                          KC_LABK,  KC_LBRC,  KC_LCBR,  KC_LPRN,  KC_GRV,   KC_QUOT,
    //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤                    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
       XXXXXXX,  XXXXXXX,  KC_1,     KC_2,     KC_3,     KC_EQL,                        KC_TILD,  KC_MINS,  KC_UNDS,  KC_EQL,   KC_PLUS,  KC_PERC,
    //└─────────┴─────────┴─────────┼─────────┼─────────┼─────────┤                    ├─────────┼─────────┼─────────┴─────────┴─────────┴─────────┘
                                     KC_DOT,   G(KC_SPC),KC_LSFT,                       KC_ENT,   KC_BSPC,  _______
    //                              └─────────┴─────────┴─────────┘                    └─────────┴─────────┴─────────┘
    )
};
