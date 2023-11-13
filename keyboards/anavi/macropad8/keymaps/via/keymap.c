#include QMK_KEYBOARD_H

#define _MAIN 0

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MAIN] = LAYOUT_ortho_2x4(
     G(KC_D), KC_UP,   C(KC_C), C(KC_V),
     KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS
  ),

  [1] = LAYOUT_ortho_2x4(
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [2] = LAYOUT_ortho_2x4(
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [3] = LAYOUT_ortho_2x4(
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  )
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
}

bool oled_task_user(void) {
  // Host Keyboard Layer Status
  oled_write_ln_P(PSTR("ANAVI Macro Pad 8"), false);
  oled_write_P(PSTR("Active layer: "), false);

  switch (get_highest_layer(layer_state)) {
    case _MAIN:
      oled_write_ln_P(PSTR("Main"), false);
      break;
    case 1:
      oled_write_ln_P(PSTR("1"), false);
      break;
    case 2:
      oled_write_ln_P(PSTR("2"), false);
      break;
    case 3:
      oled_write_ln_P(PSTR("3"), false);
      break;
    default:
      // Or use the write_ln shortcut over adding '\n' to the end of your string
      oled_write_ln_P(PSTR("N/A"), false);
  }

  // Host Keyboard LED Status
  led_t led_state = host_keyboard_led_state();
  oled_write_P(PSTR("Num Lock: "), false);
  oled_write_ln_P(led_state.num_lock ? PSTR("On") : PSTR("Off"), false);
  oled_write_P(PSTR("Caps Lock: "), false);
  oled_write_ln_P(led_state.caps_lock ? PSTR("On") : PSTR("Off"), false);
  oled_write_P(PSTR("Scroll Lock: "), false);
  oled_write_ln_P(led_state.scroll_lock ? PSTR("On") : PSTR("Off"), false);
  oled_write_P(PSTR("Backlit: "), false);
  oled_write_ln_P(is_backlight_enabled() ? PSTR("On") : PSTR("Off"), false);
#ifdef RGBLIGHT_ENABLE
  static char rgbStatusLine1[26] = {0};
  snprintf(rgbStatusLine1, sizeof(rgbStatusLine1), "RGB Mode: %d", rgblight_get_mode());
  oled_write_ln(rgbStatusLine1, false);
  static char rgbStatusLine2[26] = {0};
  snprintf(rgbStatusLine2, sizeof(rgbStatusLine2), "h:%d s:%d v:%d", rgblight_get_hue(), rgblight_get_sat(), rgblight_get_val());
  oled_write_ln(rgbStatusLine2, false);
#endif
    return false;
}
#endif
