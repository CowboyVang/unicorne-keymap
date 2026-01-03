/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

// =============================================================================
// Tapping Behavior
// =============================================================================
#define TAPPING_TERM 140
#define RETRO_TAPPING            // Tap fires on release even if held past tapping term

// =============================================================================
// Combos
// =============================================================================
#define COMBO_COUNT 17
#define COMBO_TERM 50

// =============================================================================
// Auto Shift (custom whitelist: ; ' / - =)
// =============================================================================
#define AUTO_SHIFT_TIMEOUT 175
#define AUTO_SHIFT_REPEAT        // Allow repeat when held
#define NO_AUTO_SHIFT_ALPHA      // Disable for letters (backup safety)
#define NO_AUTO_SHIFT_NUMERIC    // Disable for numbers (backup safety)
// Custom whitelist defined in keymap.c via get_custom_auto_shifted_key()
// Excludes: alpha, numeric, brackets (conflict with Key Overrides), comma, period

// =============================================================================
// Caps Word
// =============================================================================
#define CAPS_WORD_IDLE_TIMEOUT 5000  // 5 seconds

// =============================================================================
// One Shot Keys
// =============================================================================
#define ONESHOT_TAP_TOGGLE 2
#define ONESHOT_TIMEOUT 3000

// =============================================================================
// Select Word (macOS)
// =============================================================================
#define SELECT_WORD_OS_MAC
#define SELECT_WORD_TIMEOUT 2000  // 2 seconds

// =============================================================================
// RGB Matrix
// =============================================================================
// Off by default - enable via RGB keycodes
#define RGB_MATRIX_DEFAULT_VAL 0
