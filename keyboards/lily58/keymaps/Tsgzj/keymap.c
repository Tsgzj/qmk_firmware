#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif



#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#define _BASE 0
#define _LOWER 1
#define _RAISE 2
#define _FUNC 3

enum custom_keycodes { BASE = SAFE_RANGE, LOWER, RAISE, FUNC };

enum tap_dance_keycodes {
    TD_GRV = 0,
    TD_LBRC,
    TD_RBRC,
    TD_QUOT
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_COLON)
};

#define LT_LOW LT(_LOWER, KC_BSPC)
#define LT_RAI LT(_RAISE, KC_ENT)
#define BRC_LCTRL MT(MOD_LCTL, KC_LBRC)
#define BRC_FUNC LT(_FUNC, KC_RBRC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* QWERTY
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |  `~  |  1!  |  2@  |  3#  |  4$  |  5%  |                    |  6^  |  7&  |  8*  |  9(  |  0)  |  =+  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |  ESC |  '"  |  ,<  |  .>  |   P  |   Y  |                    |   F  |   G  |   C  |   R  |  L   |  ?/  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |  Tab |   A  |   O  |   E  |   U  |   I  |-------.    ,-------|   D  |   H  |   T  |   N  |  S   |  -_  |
     * |------+------+------+------+------+------| NOOP  |    |   \|  |------+------+------+------+------+------|
     * |  [{  |  ;:  |   Q  |   J  |   K  |   X  |-------|    |-------|   B  |   M  |   W  |   V  |  Z   |  ]}  |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *                   | LALT | LGUI | SHFT | / LOWER /       \ RAISE\  | SPACE| CTRL | RGUI |
     *                   |      |      |      |/       /         \      \ |      |      |      |
     *                   `----------------------------'           '------''--------------------'
     */

    [_BASE] = LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5,                   KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQL,
                     KC_ESC, KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_P,                   KC_F, KC_G, KC_C, KC_R, KC_L, KC_QUES,
                     KC_TAB, KC_A, KC_O, KC_E, KC_U, KC_I,                   KC_D, KC_H, KC_T, KC_N, KC_S, KC_MINS,
                     BRC_LCTRL, KC_SCLN, KC_Q, KC_J, KC_K, KC_X, KC_NO,         KC_BSLS, KC_B, KC_M, KC_W, KC_V, KC_Z, BRC_FUNC,
                     KC_LALT, KC_LGUI, KC_LSFT, LT_LOW, LT_RAI, KC_SPC, KC_RCTL, KC_RGUI),
    /* RAISE
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      |  F1  |  F2  |  F3  |  F4  | F5   |                    |  F6  |  F7  | F8   |  F9  | F10  | F11  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |  ~   |  *   |  -   |  +   |                    |   _  |   /  |  \   |   ,  |  .   |  `   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |  <   |  [   |  ]   |   >  |  =   |-------.    ,-------|   {  |  (   |   )  |   }  |  |   |  '   |
     * |------+------+------+------+------+------|       |    | CAPS  |------+------+------+------+------+------|
     * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *                   |      |      |      | /       /       \      \  |      |      |      |
     *                   |      |      |      |/       /         \      \ |      |      |      |
     *                   `----------------------------'           '------''--------------------'
     */
    [_RAISE] = LAYOUT(_______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                          KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
                      _______, KC_DOT, _______, KC_ASTR, KC_MINS, KC_PLUS,                          KC_UNDS, KC_SLSH, KC_BSLS, KC_COMM, KC_DOT, KC_GRV,
                      _______, KC_LABK, KC_LBRC, KC_RBRC, KC_RABK, KC_QUES,      KC_LCBR, KC_LPRN, KC_RPRN, KC_RCBR, KC_PIPE, TD_QUOT,
                      _______, _______, _______, _______, _______, _______, _______, KC_CAPS, _______, _______, _______, _______, _______, _______,
                      _______,_______, KC_0, KC_BSPC, _______, _______, _______, _______),
    /* LOWER
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      |      |      |      |      |      |                    |      |   .  |   /  |   *  |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |      |   7  |   8  |   9  |  +   |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |  F6  |  F7  |  F8  |  F9  | F10  |-------.    ,-------|      |   4  |   5  |   6  |  -   |      |
     * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
     * |      | F11  | F12  | F13  | F14  | F15  |-------|    |-------|   0  |   1  |   2  |   3  |  =   |      |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *                   |      |      |      | /       /       \      \  |      |      |
     *                   |      |      |      |/       /         \      \ |      |      |      |
     *                   `----------------------------'           '------''--------------------'
     */

    [_LOWER] = LAYOUT(_______, _______, _______, _______, _______, _______,     _______, KC_DOT, KC_SLSH, KC_ASTR, _______, _______,
                      _______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,               XXXXXXX, KC_7, KC_8, KC_9, KC_PLUS, _______,
                      _______, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,              XXXXXXX, KC_4, KC_5, KC_6, KC_MINS, XXXXXXX,
                      _______, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, _______,   _______, KC_0, KC_1, KC_2, KC_3, KC_EQL, _______,
                      _______, _______, _______, _______,                       KC_ENT, _______, _______, _______),
    /* FUNC
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      |      |      |      |      |      |                    | MPRV | MPLY | MNXT |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |      |      |      |                    | HOME | PGUP | PGDN | END  |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |      |      |      |-------.    ,-------| Left | Down |  UP  | Right|      |      |
     * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
     * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *                   |      |      |      | /       /       \      \  |      |      |      |
     *                   |      |      |      |/       /         \      \ |      |      |      |
     *                   `----------------------------'           '------''--------------------'
     */

    [_FUNC] = LAYOUT(_______, _______, _______, _______, _______, _______,         KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______,
                     _______, _______, _______, _______, _______, _______,         KC_HOME, KC_PGDN, KC_PGUP, KC_END, _______, _______,
                     _______, _______, _______, _______, _______, _______,         KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, XXXXXXX, XXXXXXX,
                     _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______,
                     _______, _______, _______, _______,                           _______, _______, _______, _______)};

int RGB_current_mode;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        switch (biton32(layer_state)) {
        case 2:
            if(clockwise) {
                tap_code(KC_MNXT);
            } else {
                tap_code(KC_MPRV);
            }
            break;
        default:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        }
    }
}

#ifdef OLED_DRIVER_ENABLE
static char     keylog_str[6]   = {};
static uint16_t log_timer       = 0;
static const char PROGMEM code_to_name[0xFF] = {
//   0    1    2    3    4    5    6    7    8    9    A    B    c    D    E    F
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',  // 0x
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2',  // 1x
    '3', '4', '5', '6', '7', '8', '9', '0',  20,  19,  27,  26,  22, '-', '=', '[',  // 2x
    ']','\\', '#', ';','\'', '`', ',', '.', '/', 128, ' ', ' ', ' ', ' ', ' ', ' ',  // 3x
    ' ', ' ', ' ', ' ', ' ', ' ', 'P', 'S', ' ', ' ', ' ', ' ',  16, ' ', ' ', ' ',  // 4x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 5x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 6x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 7x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 8x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 9x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ax
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Bx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Cx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Dx
    'C', 'S', 'A', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ex
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '        // Fx
};

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return OLED_ROTATION_180;
    }

    return rotation;
}

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

void add_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
        keycode = keycode & 0xFF;
    } else if (keycode > 0xFF) {
        keycode = 0;
    }

    for (uint8_t i = 4; i > 0; --i) {
        keylog_str[i] = keylog_str[i - 1];
    }

    if (keycode < (sizeof(code_to_name) / sizeof(char))) {
        keylog_str[0] = pgm_read_byte(&code_to_name[keycode]);
    }

    log_timer = timer_read();
}

void render_layer_status(void) {
    oled_write_P(PSTR("LAYER"), false);
    oled_write_P(PSTR("BASE\n"), layer_state_is(_BASE));
    oled_write_P(PSTR("SYMB\n"), layer_state_is(_RAISE));
    oled_write_P(PSTR("NUM\n"), layer_state_is(_LOWER));
    oled_write_P(PSTR("FUNC\n"), layer_state_is(_FUNC));
    oled_write_P(PSTR("\n"), false);
}

void render_mod_status(uint8_t modifiers) {
    oled_write_P(PSTR("MODS\n"), false);
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_ln_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
    oled_write_P(PSTR("\n"), false);
}

void render_keylock_status(uint8_t led_usb_state) {
    oled_write_P(PSTR("LOCK\n"), false);
    oled_write_P(PSTR("N"), led_usb_state & (1 << USB_LED_NUM_LOCK));
    oled_write_P(PSTR("C"), led_usb_state & (1 << USB_LED_CAPS_LOCK));
    oled_write_ln_P(PSTR("S"), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
    oled_write_P(PSTR("\n"), false);
}

void render_keylogger_status(void) {
    oled_write_P(PSTR("KLGGR"), false);
    oled_write(keylog_str, false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_layer_status();
        render_mod_status(get_mods()|get_oneshot_mods());
        render_keylock_status(host_keyboard_leds());
        render_keylogger_status();
    } else {
        render_logo();  // Renders a static logo
    }
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
      add_keylog(keycode);
#endif
  }

  switch (keycode) {
  case BASE:
      if (record->event.pressed) {
          set_single_persistent_default_layer(_BASE);
      }
      return false;
      break;
  case LOWER:
      if (record->event.pressed) {
          layer_on(_LOWER);
      } else {
          layer_off(_LOWER);
      }
      return false;
      break;
  case RAISE:
      if (record->event.pressed) {
          layer_on(_RAISE);
      } else {
          layer_off(_RAISE);
      }
      return false;
      break;
  case FUNC:
      if (record->event.pressed) {
          layer_on(_FUNC);
      } else {
          layer_off(_FUNC);
      }
      return false;
      break;
  }
  return true;
}
