#include QMK_KEYBOARD_H
//macros
enum custom_keycodes {
    VIM_G = SAFE_RANGE,
    NEOTREE,
    FOUND,
    TMUX_SPLIT,
    TMUX_LEFT,
    COPIAR,
    QUIT
};

// Distro
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_3x3(
        VIM_G,      NEOTREE,    FOUND,
        TMUX_SPLIT, TMUX_LEFT,  COPIAR,
        FOUND,       COPIAR,       QUIT       )
};


/*La distro real que logré con el hardware:
*
*        | Ctrl+B | Ctrl+F
* FOUND  | :w!    |TMUX_SPLIT
* COPIAR | Ctrl+n | TMUX_LEFT
*
*/

// 3. Lógica de las macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case VIM_G:
          if (record->event.pressed) {
                tap_code(KC_ESC);
                wait_ms(15); //Sin el delay no funciona :(
                tap_code16(LSFT(KC_DOT));

                tap_code(KC_W);

        // La exclamación (!) es Shift + 1
                tap_code16(LSFT(KC_1));

                tap_code(KC_ENT);
            }
            break;

        case NEOTREE:
            if (record->event.pressed) {
                tap_code16(KC_ESC);
                wait_ms(10);
                tap_code16(LCTL(KC_N));
            }
            break;

        case TMUX_SPLIT:
            if (record->event.pressed) {
                tap_code16(LCTL(KC_B));
                wait_ms(10);
                tap_code16(KC_PERC);
            }
            break;

        case TMUX_LEFT:
            if (record->event.pressed) {
                tap_code16(LCTL(KC_B));
                wait_ms(10);
                tap_code(KC_LEFT);
            }
            break;

        case COPIAR:
            if (record->event.pressed) {
                tap_code(KC_ESC);
                tap_code16(KC_DQUO); // Comilla doble "
                tap_code16(KC_PLUS);
                tap_code(KC_Y);
            }
            break;

        case FOUND:
            if (record->event.pressed) {
                tap_code(KC_ESC);
                tap_code16(LCTL(KC_F));
            }
            break;

        case QUIT:
            if (record->event.pressed) {
                tap_code(KC_ESC);
                SEND_STRING(":q" SS_TAP(X_ENTER));
            }
            break;
    }
    return true;
};
