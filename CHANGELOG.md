# Changelog - Pure QMK Keymap

All notable changes to the pure QMK keymap for Boardsource Unicorne.

## [2.0.10] - 2025-12-29

### Added
- **Keymap Visualizations** - Added layer and combo diagram images to README
  - `layer-0-base.png` - Base layer (Colemak-DH)
  - `layer-1-nav.png` - Navigation layer
  - `layer-2-sym.png` - Symbols layer
  - `combos-horizontal-vertical.png` - Horizontal and vertical combos
  - `combos-diagonal.png` - Diagonal combos
- **Nordic.nvim Attribution** - Color scheme credit with link to source

### Changed
- **Image Naming** - Standardized to lowercase with descriptive suffixes

---

## [2.0.9] - 2025-12-29

### Added
- **README: Hardware Specifications** - Added case, switches, and keycaps details
  - Unicorne LP Aluminum Case for chording stability
  - Ambients Silent Choc switches for low pinky fatigue
  - Blank MBK keycaps for vertical chording technique
- **README: Ergonomics & Finger Mapping** - Added home row positions and finger-to-key mapping

---

## [2.0.8] - 2025-12-28

### Changed
- **Tab key** - `KC_TAB` → `LCTL_T(KC_TAB)` (Tap = Tab, Hold = Control)

---

## [2.0.7] - 2025-12-28

### Changed
- **Combos redesigned** - Expanded from 6 to 11 combos with logical groupings
  - **Left Hand Vertical**: W+R=Esc, F+S=Tab
  - **Left Hand Horizontal**: F+P=Del, X+C=Undo, C+D=Redo, D+V=Paste plain
  - **Left Hand Diagonal**: F+T=Backspace
  - **Right Hand Vertical**: U+E=Pipe, Y+I=Backtick, L+N=CapsWord
  - **Right Hand Diagonal**: N+U=Shift+Enter
- **Removed combos**: Q+W (CapsWord moved to L+N), P+B (Delete moved to F+P), W+F (Esc moved to W+R)
- **COMBO_COUNT** - Updated from 6 to 11

---

## [2.0.6] - 2025-12-28

### Added
- **Space Cadet** - `SC_LSPO` and `SC_RSPC` for parentheses on shift keys
  - Left shift tap = `(`, Right shift tap = `)`
  - Hold = normal Shift behavior
- **SPACE_CADET_ENABLE** - Added to rules.mk
- **RETRO_TAPPING** - Tap fires on release even if held past tapping term
  - Fixes comma/period reliability with `HYPR_T` and `MEH_T` mod-taps

### Changed
- **Layer 0 redesign**:
  - `KC_ESC` → `LALT_T(KC_ESC)` (Tap = Esc, Hold = Alt)
  - `KC_LSFT` → `SC_LSPO` (Space Cadet left paren)
  - `KC_MINS` → `KC_BSLS` (top right pinky now backslash)
  - `KC_COMM` → `HYPR_T(KC_COMM)` (Tap = `,`, Hold = Hyper)
  - `KC_DOT` → `MEH_T(KC_DOT)` (Tap = `.`, Hold = Meh)
  - `KC_BSLS` → `SC_RSPC` (Space Cadet right paren)
- **Layer 0 thumbs**:
  - Left outer: `MO(_NAV)` → `LT(_NAV, KC_MINS)` (Tap = `-`, Hold = Nav)
  - Left inner: `KC_LGUI` → `LGUI_T(KC_EQL)` (Tap = `=`, Hold = Cmd)
  - Right outer: `OSM(MOD_LSFT)` → `RALT_T(KC_NO)` (Hold = Alt)
- **Layer 1**:
  - Bottom row col 3: `KC_MINS` → `S(KC_MINS)` (underscore `_`)
  - Right outer thumb: `_______` → `KC_DEL` (Delete key)

---

## [2.0.5] - 2025-12-28

### Fixed
- **Auto Shift for alphas** - Re-added `NO_AUTO_SHIFT_ALPHA` and `NO_AUTO_SHIFT_NUMERIC` to config.h
- **Layer 1 thumb** - Changed `KC_DEL` to `KC_BSPC` on right middle thumb

### Changed
- **README** - Added detailed thumb cluster sections for Layer 1 and Layer 2

---

## [2.0.4] - 2025-12-27

### Changed
- **Auto Shift redesigned** - Custom whitelist replaces default behavior
  - Now only applies to: `;` `:`, `'` `"`, `/` `?`, `-` `_`, `=` `+`
  - Brackets removed from Auto Shift (conflicted with Key Overrides)
  - Comma and period excluded (already have `<` `>` on Layer 2)
- **Key Overrides** - Now the sole method for bracket pairs (`Shift+[` = `]`)

### Fixed
- **Bracket behavior** - Holding `[` no longer produces `{` (Auto Shift conflict resolved)

---

## [2.0.3] - 2025-12-27

### Changed
- **Layer 0**: Replaced `CW_TOGG` with `KC_LSFT` on bottom-left pinky
- **Layer 1 (NAV)**: Rearranged navigation to vim-style (Left/Down/Up/Right)
  - Moved `KC_INS` to top row, `KC_UP` to home row
  - Added math operators on bottom row: `KC_MINS`, `KC_MINS`, `KC_PLUS`, `KC_EQL`
- **Layer 2 (SYM)**: Moved `KC_P0` from thumb to home row (Col 6)
  - Thumb middle now `G(KC_SPC)` (Cmd+Space / Spotlight/Raycast)

---

## [2.0.2] - 2025-12-27

### Changed
- **Auto Shift now only for brackets** - Removed `NO_AUTO_SHIFT_SPECIAL` to enable auto shift for bracket keys
  - Hold `[`, `(`, or `{` to get closing bracket via Auto Shift
  - Alpha and numeric keys remain unaffected
- Removed `AUTO_SHIFT_NO_SETUP` - Auto Shift now enabled by default

---

## [2.0.1] - 2025-12-27

### Changed
- **Right thumb cluster redesigned**:
  - Inner: `RSFT_T(KC_ENT)` - Tap = Enter, Hold = Shift
  - Mid: `LT(_SYM, KC_BSPC)` - Tap = Backspace, Hold = Sym layer
  - Outer: `OSM(MOD_LSFT)` - One-shot Shift
- **Layer 2 left inner thumb** - Changed from `KC_LGUI` to `KC_LSFT`

---

## [2.0.0] - 2025-12-27

### BREAKING CHANGES
- **Complete layout overhaul** - Reduced from 5 layers to 3 layers
- **Removed Space Cadet** - No more SC_LSPO, SC_RSPC, SC_SENT
- **Removed Tap Dance** - Shift/Caps Lock tap dance removed

### Added
- **Pure Space design** - KC_SPC on left middle thumb (no layer-tap delay)
- **Caps Word** - Enabled with CW_TOGG on left pinky, 5s idle timeout
- **Key Overrides for brackets** - Shift+[ = ], Shift+( = ), Shift+{ = }
- **4 new combos** - W+F=Esc, P+B=Del, F+P=Tab, Q+W=CapsWord
- **NO_AUTO_SHIFT_ALPHA** - Prevents accidental caps during fast typing

### Changed
- **Thumb cluster redesigned**:
  - Left: MO(_NAV) / KC_SPC / KC_LGUI
  - Right: RSFT_T(KC_ENT) / KC_BSPC / MO(_SYM)
- **Layer 1 (NAV)** - Now includes full navigation (arrows, PgUp/Dn, Home/End) on right side
- **Layer 2 (SYM)** - Merged numpad (left) and symbols (right) into one layer
- **Combos expanded** - From 2 to 6 combos
- **COMBO_COUNT** - Updated from 2 to 6

### Removed
- **Layer 3 (Numpad)** - Merged into Layer 2
- **Layer 4 (System)** - Removed entirely
- **TAP_DANCE_ENABLE** - Feature disabled
- **SPACE_CADET_ENABLE** - Feature disabled
- **Home row mods on base layer** - Removed LCTL_T(TAB), LALT_T(ESC), etc.

---

## [1.3.0] - 2025-12-26

### Changed
- **Auto Shift off by default** - Added `AUTO_SHIFT_NO_SETUP` to config.h
  - Toggle on with AS_TOGG when needed

### Removed
- **Mousekeys disabled** - Set `"mousekey": false` in keyboard.json

---

## [1.2.0] - 2025-12-26

### Removed
- **Key Overrides** - Removed feature entirely (was: Shift+U=Pipe, Shift+K=Shift+Enter)
  - Disabled `KEY_OVERRIDE_ENABLE` in rules.mk
  - Removed `key_overrides[]` array from keymap.c

### Changed
- **Combos updated** - New key combinations
  - U + E = Pipe `|` (was U + Y)
  - N + U = Shift+Enter (was K + H)

---

## [1.1.0] - 2025-12-26

### Fixed
- **Mouse drift issue** - Disabled `pointing_device` in keyboard.json
  - Per Boardsource build guide: causes drift on some computers when no joystick installed
  - Set `"pointing_device": false` to resolve

### Changed
- **Audio disabled** - Set `"audio": false` in keyboard.json
  - No audio hardware installed
  - Prevents unnecessary feature compilation

### Added
- `README.md` - Keymap documentation with layer diagrams
- `CLAUDE.md` - Claude Code instructions for this keymap
- `CHANGELOG.md` - This file

---

## [1.0.0] - 2025-12-26

### Added
- Initial 5-layer Colemak-DH keymap

**Layer 0 (Base)**: Colemak-DH with mod-taps
- `LCTL_T(KC_TAB)`, `LALT_T(KC_ESC)`
- Space Cadet: `SC_LSPO`, `SC_RSPC`, `SC_SENT`
- Hyper/Meh on comma/period
- Layer-tap thumbs: `LT(_NAV,KC_BSPC)`, `LT(_SYM,KC_BSPC)`

**Layer 1 (Navigation)**: F15-F20 with modifiers + arrows
- Home row mods on F16-F19
- Shift+F15-F20 (top row)
- Cmd+Shift+F15-F20 (bottom row)
- Auto Shift controls (AS_TOGG, AS_ON, AS_OFF)
- QK_AREP for repeat key

**Layer 2 (Symbols)**: Numbers and symbols
- Symbols on top row (!@#$%^&*())
- Numbers on home row (1234567890)
- Brackets on outer columns
- Grave/tilde access

**Layer 3 (Numpad)**: Calculator-style numpad on left side

**Layer 4 (System)**: Recovery
- QK_BOOT for bootloader
- EE_CLR for EEPROM clear

### Features Enabled
- Tap Dance (1 action: Shift/Caps Lock)
- Combos (2 combos: U+E=Pipe, N+U=Shift+Enter)
- Auto Shift (150ms timeout, no special/numeric)
- Space Cadet
- OLED Display
- Encoder
- RGB Matrix (off by default)
- Mousekeys

### Disabled
- Audio (no hardware)
- Pointing Device (causes mouse drift)

---

## Version Format

Versions follow [Semantic Versioning](https://semver.org/):
- **MAJOR**: Breaking keymap changes (layer restructure, removed keys)
- **MINOR**: New features, bug fixes, config changes
- **PATCH**: Documentation updates only
