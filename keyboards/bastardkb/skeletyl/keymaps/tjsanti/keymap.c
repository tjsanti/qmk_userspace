/* 
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum custom_keycodes {
    KC_DOT_COL = SAFE_RANGE,
    KC_COM_SEM
};

enum layer_names {
    _ALPHA,
    _NUM,
    _SYM,
    _NAV
};


// Define each combo key pair and the corresponding output
enum combo_events {
    COMBO_RS_BSPC,
    COMBO_SN_TAB,
    COMBO_NT_COPY,
    COMBO_MG_CUT,
    COMBO_DV_PASTE,
    COMBO_ZW_UNDO,
    COMBO_AE_UNDERSCORE,
    COMBO_EI_EXCLAMATION,
    COMBO_IH_QUESTION,
    COMBO_AT_CAPSWORD,
    COMBO_LENGTH
};

const uint16_t PROGMEM combo_rs_bspc[] = {WIN_T(KC_R), ALT_T(KC_S), COMBO_END};
const uint16_t PROGMEM combo_sn_tab[] = {ALT_T(KC_S), CTL_T(KC_N), COMBO_END};
const uint16_t PROGMEM combo_nt_copy[] = {KC_N, KC_T, COMBO_END};
const uint16_t PROGMEM combo_mg_cut[] = {KC_M, KC_G, COMBO_END};
const uint16_t PROGMEM combo_dv_paste[] = {KC_D, KC_V, COMBO_END};
const uint16_t PROGMEM combo_zw_undo[] = {KC_Z, KC_W, COMBO_END};
const uint16_t PROGMEM combo_ae_underscore[] = {SFT_T(KC_A), CTL_T(KC_E), COMBO_END};
const uint16_t PROGMEM combo_ei_exclamation[] = {CTL_T(KC_E), ALT_T(KC_I), COMBO_END};
const uint16_t PROGMEM combo_ih_question[] = {ALT_T(KC_I), WIN_T(KC_H), COMBO_END};
const uint16_t PROGMEM combo_at_capsword[] = {SFT_T(KC_A), SFT_T(KC_T), COMBO_END};

combo_t key_combos[COMBO_LENGTH] = {
    [COMBO_RS_BSPC] = COMBO(combo_rs_bspc, KC_BSPC),
    [COMBO_SN_TAB] = COMBO(combo_sn_tab, KC_TAB),
    [COMBO_NT_COPY] = COMBO(combo_nt_copy, LCTL(KC_C)),
    [COMBO_MG_CUT] = COMBO(combo_mg_cut, LCTL(KC_X)),
    [COMBO_DV_PASTE] = COMBO(combo_dv_paste, LCTL(KC_V)),
    [COMBO_ZW_UNDO] = COMBO(combo_zw_undo, LCTL(KC_Z)),
    [COMBO_AE_UNDERSCORE] = COMBO(combo_ae_underscore, KC_UNDS),
    [COMBO_EI_EXCLAMATION] = COMBO(combo_ei_exclamation, KC_EXLM),
    [COMBO_IH_QUESTION] = COMBO(combo_ih_question, KC_QUES),
    [COMBO_AT_CAPSWORD] = COMBO(combo_at_capsword, CW_TOGG)
};

bool get_combo_must_tap(uint16_t index, combo_t *combo) {
    // If you want all combos to be tap-only, uncomment the next line
    // return true;

    // If you want *all* combos that have Mod-Tap/Layer-Tap/Momentary keys in their chord to be tap-only, this is for you:
    uint16_t key;
    uint8_t idx = 0;
    while ((key = pgm_read_word(&combo->keys[idx])) != COMBO_END) {
        switch (key) {
            case QK_MOD_TAP...QK_MOD_TAP_MAX:
            case QK_LAYER_TAP...QK_LAYER_TAP_MAX:
            case QK_MOMENTARY...QK_MOMENTARY_MAX:
                return true;
        }
        idx += 1;
    }
    return false;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_ALPHA] = LAYOUT_split_3x5_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_Z,    KC_W,    KC_M,    KC_G,    KC_Q,                         KC_QUOT,    KC_DOT_COL,    KC_K,    KC_J,   XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      WIN_T(KC_R),    ALT_T(KC_S),    CTL_T(KC_N),    SFT_T(KC_T),    KC_P,                         KC_COM_SEM,    SFT_T(KC_A),    CTL_T(KC_E),    ALT_T(KC_I), WIN_T(KC_H),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_L,    KC_C,    KC_D,    KC_V,    KC_B,                         KC_X,    KC_O, KC_U,  KC_Y, KC_F, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          LT(_NAV, KC_ENT), LT(_NUM, KC_SPC),   QK_AREP,     QK_REP, MO(_SYM), KC_ESC
                                      //`--------------------------'  `--------------------------'

  ),

  [_NUM] = LAYOUT_split_3x5_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                      KC_PLUS,    KC_7,   KC_8,   KC_9,   KC_ASTR,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LWIN,  KC_LALT,    KC_LCTL,    KC_LSFT,    XXXXXXX,                      _______,    KC_4,   KC_5,   KC_6,   KC_DOT_COL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                      KC_MINS,    KC_1,   KC_2,   KC_3,   KC_SLSH,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, _______, XXXXXXX,    XXXXXXX, KC_0, KC_BSPC
                                      //`--------------------------'  `--------------------------'
  ),

  [_SYM] = LAYOUT_split_3x5_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_LT,   KC_GT, KC_LCBR,  KC_RCBR, KC_GRV,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS,                      XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_PIPE, KC_SLSH, KC_LBRC, KC_RBRC, KC_MINS,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_BSLS,  _______,  KC_EQL,     XXXXXXX, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [_NAV] = LAYOUT_split_3x5_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, KC_UP, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,  KC_SPC, _______,     _______, KC_ENT, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_DOT_COL:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    tap_code16(KC_COLN);  // Colon when shifted
                } else {
                    tap_code(KC_DOT);     // Period otherwise
                }
            }
            return false;
            
        case KC_COM_SEM:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    tap_code16(KC_SCLN);  // Semicolon when shifted
                } else {
                    tap_code(KC_COMM);    // Comma otherwise
                }
            }
            return false;
            
        default:
            return true;
    }
}