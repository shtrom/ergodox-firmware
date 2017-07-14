/* ----------------------------------------------------------------------------
* ergoDOX layout : QWERTY (modified from the Kinesis layout)
* -----------------------------------------------------------------------------
* Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
* Released under The MIT License (MIT) (see "license.md")
* Project located at <https://github.com/benblazak/ergodox-firmware>
* -------------------------------------------------------------------------- */
#include <stdint.h>
#include <stddef.h>
#include <avr/pgmspace.h>
#include "../../../lib/data-types/misc.h"
#include "../../../lib/usb/usage-page/keyboard--short-names.h"
#include "../../../lib/key-functions/public.h"
#include "../../../lib-other/pjrc/usb_keyboard/usb_keyboard.h"
#include "../../../main.h"
#include "../matrix.h"
#include "../layout.h"
// FUNCTIONS ------------------------------------------------------------------
void kbfun_layer_pop_all(void) {
  kbfun_layer_pop_1();
  kbfun_layer_pop_2();
  kbfun_layer_pop_3();
  kbfun_layer_pop_4();
  kbfun_layer_pop_5();
  kbfun_layer_pop_6();
  kbfun_layer_pop_7();
  kbfun_layer_pop_8();
  kbfun_layer_pop_9();
  kbfun_layer_pop_10();
}

void layer_to_led(int layer)
{
	switch(layer) {
	case 0:
		keyboard_leds = 0;
		break;
	case 1:
	case 2:
	case 3:
		keyboard_leds = (1<<(layer-1));
		break;
	default:
		keyboard_leds = 255;
		break;
	}
}

// Template functions to set LEDs on and off
#define led_layer(layer) \
	void llpush ## layer (void) { \
		kbfun_layer_push_ ## layer (); \
		layer_to_led(main_layers_peek(main_arg_layer_offset)); \
	} \
	void llpop ## layer (void) { \
		kbfun_layer_pop_ ## layer (); \
		layer_to_led(main_layers_peek(main_arg_layer_offset)); \
	} \
	void llsticky ## layer (void) { \
		kbfun_layer_sticky_ ## layer (); \
		layer_to_led(main_layers_peek(main_arg_layer_offset)); \
	}
// Make sure the LEDs are updated for when a key is p/r after a sticky key
void lkbfun_press_release() {
	kbfun_press_release();
	layer_to_led(main_layers_peek(main_arg_layer_offset));
}

// Declare the function for the first 3 alternative layers
led_layer(1);
led_layer(2);
led_layer(3);

// DEFINITIONS ----------------------------------------------------------------
#define  kprrel   &lkbfun_press_release
#define  ktog     &kbfun_toggle
#define  ktrans   &kbfun_transparent
#define  lpush1   &kbfun_layer_push_1
#define  lpush2   &kbfun_layer_push_2
#define  lpush3   &kbfun_layer_push_3
#define  lpush4   &kbfun_layer_push_4
#define  lpush5   &kbfun_layer_push_5
#define  lpush6   &kbfun_layer_push_6
#define  lpush7   &kbfun_layer_push_7
#define  lpush8   &kbfun_layer_push_8
#define  lpush9   &kbfun_layer_push_9
#define  lpush10  &kbfun_layer_push_10
#define  lpop     &kbfun_layer_pop_all
#define  lpop1    &kbfun_layer_pop_1
#define  lpop2    &kbfun_layer_pop_2
#define  lpop3    &kbfun_layer_pop_3
#define  lpop4    &kbfun_layer_pop_4
#define  lpop5    &kbfun_layer_pop_5
#define  lpop6    &kbfun_layer_pop_6
#define  lpop7    &kbfun_layer_pop_7
#define  lpop8    &kbfun_layer_pop_8
#define  lpop9    &kbfun_layer_pop_9
#define  lpop10   &kbfun_layer_pop_10
#define  dbtldr   &kbfun_jump_to_bootloader
#define  sshprre  &kbfun_shift_press_release
#define  s2kcap   &kbfun_2_keys_capslock_press_release
#define  slpunum  &kbfun_layer_push_numpad
#define  slponum  &kbfun_layer_pop_numpad
// ----------------------------------------------------------------------------


// LAYOUT ---------------------------------------------------------------------
const uint8_t PROGMEM _kb_layout[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {
// LAYER 0: QWERTY, with a few weird keys so they work well in Dvorak
KB_MATRIX_LAYER(
	// unused
	0,
	// left hand
	_grave,	_1,	_2,	_3,	_4,	_5,	_esc,
	_tab,	_Q,	_W,	_E,	_R,	_T,	_bs,
	_shiftL,_A,	_S,	_D,	_F,	_G,
	_ctrlL,	_Z,	_X,	_C,	_V,	_B,	_enter,
	_guiL,	_sysReq,_home,	_end,	_altL,
	// left thumb
		_bracketL,2,
	0,	0,	_pageU,
	_space,	_dash,	_pageD,
	// right hand
	_del,	_6,	_7,	_8,	_9,	_0,		_bracketR,
	_bs,	_Y,	_U,	_I,	_O,	_P,		_quote,
		_H,	_J,	_K,	_L,	_semicolon,	_shiftR,
	_enter,	_N,	_M,	_comma,	_period,_slash,		_ctrlR,
			_altR,	_arrowL,_arrowR,_print,		_guiR,
	// right thumb
	1,	_backslash,
	_arrowU,	0,	0,
	_arrowD,	_equal,	_space
),
// LAYER 1: Media and shortcut keys
KB_MATRIX_LAYER(
	// unused
	0,
	// left hand
	0,	_F1,	_F2,	_F3,	_F4,	_F5,	_F11,
	3,	0,	0,	0,	0,	0,	0,
	3,	0,	0,	0,	0,	0,
	0,	0,	KEY_Cut,	KEY_Copy,	KEY_Paste,	0,	0,
	0,	0,	KEY_Mute,	KEY_VolumeDown,	KEY_VolumeUp,
	// left thumb
		0,	3,
	0,	0,	0,
	0,	0,	0,
	// right hand
	_F12,	_F6,	_F7,	_F8,	_F9,	_F10,	KEY_Power,
	0,	0,	0,	0,	0,	0,	0,
		0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,
	MEDIAKEY_PREV_TRACK,	MEDIAKEY_PLAY_PAUSE,	MEDIAKEY_NEXT_TRACK,	0,	KEY_Menu,
	// right thumb
	1,	0,
	0,	0,	0,
	0,	0,	0
),
// LAYER 2: Additional function keys and keypad
KB_MATRIX_LAYER(
	// unused
	0,
	// left hand
	0,	0,	0,	KEY_CapsLock,	KEY_ScrollLock,	0,	0,
	0,	0,	_home,	_arrowU,	_pageU,	0,	0,
	0,	0,	_arrowL,	0,	_arrowR,	0,
	0,	0,	_end,	_arrowD,	_pageD,	0,	0,
	0,	0,	0,	KEY_Insert,	_del,
	// left thumb
		0,	2,
	0,	0,	0,
	0,	0,	0,
	// right hand
	0,	0,	KEYPAD_NumLock_Clear,	KEYPAD_Slash,	KEYPAD_Asterisk,	KEYPAD_Minus,	0,
	0,	0,	KEYPAD_7_Home,	KEYPAD_8_UpArrow,	KEYPAD_9_PageUp,	KEYPAD_Plus,	0,
		0,	KEYPAD_4_LeftArrow,	KEYPAD_5,	KEYPAD_6_RightArrow,	KEYPAD_Plus,	0,
	0,	0,	KEYPAD_1_End,	KEYPAD_2_DownArrow,	KEYPAD_3_PageDown,	_enter,	0,
	KEYPAD_0_Insert,	KEYPAD_0_Insert,	KEYPAD_Period_Delete,	0,	0,
	// right thumb
	3,	0,
	0,	0,	0,
	0,	0,	0
),
// LAYER 3: Hard-remapped DVORAK, for when the OS can't do it
KB_MATRIX_LAYER(
	// unused
	0,
	// left hand
	_grave,	_1,	_2,	_3,	_4,	_5,	_esc,
	_tab,	_quote,	_comma,	_period,_P,	_Y,	_bs,
	_shiftL,_A,	_O,	_E,	_U,	_I,
	_ctrlL,	_semicolon,_Q,	_J,	_K,	_X,	_enter,
	_guiL,	_sysReq,_home,	_end,	_altL,
	// left thumb
		_slash,2,
	0,	0,	_pageU,
	_space, _bracketL,_pageD,
	// right hand
	_del,	_6,	_7,	_8,	_9,	_0,	_equal,
	_bs,	_F,	_G,	_C,	_R,	_L,	_dash,
		_D,	_H,	_T,	_N,	_S,	_shiftR,
	_enter,	_B,	_M,	_W,	_V,	_Z,	_ctrlR,
			_altR,	_arrowL,_arrowR,_print,	_guiR,
	// right thumb
	1,	_backslash,
	_arrowU,	0,	0,
	_arrowD,	_bracketR,	_space
),
// LAYER 4
KB_MATRIX_LAYER(
	// unused
	0,
	// left hand
	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,
	// left thumb
		0,	0,
	0,	0,	0,
	0,	0,	0,
	// right hand
	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,
		0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,
	// right thumb
	0,	0,
	0,	0,	0,
	0,	0,	0
),
// LAYER 5
KB_MATRIX_LAYER(
	// unused
	0,
	// left hand
	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,
	// left thumb
		0,	0,
	0,	0,	0,
	0,	0,	0,
	// right hand
	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,
		0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,
	// right thumb
	0,	0,
	0,	0,	0,
	0,	0,	0
),
// LAYER 6
KB_MATRIX_LAYER(
	// unused
	0,
	// left hand
	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,
		0,	0,	0,	0,	0,
	// left thumb
		0,	0,
	0,	0,	0,
	0,	0,	0,
	// right hand
	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,
		0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,
	// right thumb
	0,	0,
	0,	0,	0,
	0,	0,	0
),
// LAYER 7
KB_MATRIX_LAYER(
	// unused
	0,
	// left hand
	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,
	// left thumb
		0,	0,
	0,	0,	0,
	0,	0,	0,
	// right hand
	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,
		0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,
	// right thumb
	0,	0,
	0,	0,	0,
	0,	0,	0
),
// LAYER 8
KB_MATRIX_LAYER(
	// unused
	0,
	// left hand
	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,
	// left thumb
		0,	0,
	0,	0,	0,
	0,	0,	0,
	// right hand
	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,
		0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,
	// right thumb
	0,	0,
	0,	0,	0,
	0,	0,	0
),
// LAYER 9
KB_MATRIX_LAYER(
	// unused
	0,
	// left hand
	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,
	// left thumb
		0,	0,
	0,	0,	0,
	0,	0,	0,
	// right hand
	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,
		0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,
	// right thumb
	0,	0,
	0,	0,	0,
	0,	0,	0
),
};
// ----------------------------------------------------------------------------

// PRESS ----------------------------------------------------------------------
const void_funptr_t PROGMEM _kb_layout_press[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {
// LAYER 0
KB_MATRIX_LAYER(
	// unused
	NULL,
	// left hand
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	// left thumb
		kprrel,	llsticky2,
	NULL,	NULL,	kprrel,
	kprrel,	kprrel,	kprrel,
	// right hand
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
		kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	// right thumb
	llsticky1,kprrel,
	kprrel,	NULL,	NULL,
	kprrel,	kprrel,	kprrel
),
// LAYER 1
KB_MATRIX_LAYER(
	// unused
	NULL,
	// left hand
	dbtldr,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	ktrans,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	ktrans,	NULL,	kprrel,	kprrel,	kprrel,	NULL,	ktrans,
	ktrans,	ktrans,	kprrel,	kprrel,	kprrel,
	// left thumb
		ktrans,	lpush3,
	NULL,	NULL,	ktrans,
	ktrans,	ktrans,	ktrans,
	// right hand
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	ktrans,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
		NULL,	NULL,	NULL,	NULL,	NULL,	ktrans,
	ktrans,	NULL,	NULL,	NULL,	NULL,	NULL,	ktrans,
	kprrel,	kprrel,	kprrel,	ktrans,	kprrel,
	// right thumb
	llsticky1,	ktrans,
	ktrans,	NULL,	NULL,
	ktrans,	ktrans,	ktrans
),
// LAYER 2
KB_MATRIX_LAYER(
	// unused
	NULL,
	// left hand
	NULL,	NULL,	NULL,	kprrel,	kprrel,	NULL,	ktrans,
	ktrans,	NULL,	kprrel,	kprrel,	kprrel,	NULL,	ktrans,
	ktrans,	NULL,	kprrel,	NULL,	kprrel,	NULL,
	ktrans,	NULL,	kprrel,	kprrel,	kprrel,	NULL,	ktrans,
	ktrans,	ktrans,	ktrans,	kprrel,	kprrel,
	// left thumb
		ktrans,	llsticky2,
	NULL,	NULL,	ktrans,
	ktrans,	ktrans,	ktrans,
	// right hand
	ktrans,	NULL,	kprrel,	kprrel,	kprrel,	kprrel,	NULL,
	ktrans,	NULL,	kprrel,	kprrel,	kprrel,	kprrel,	NULL,
		NULL,	kprrel,	kprrel,	kprrel,	kprrel,	ktrans,
	ktrans,	NULL,	kprrel,	kprrel,	kprrel,	kprrel,	ktrans,
	kprrel,	kprrel,	kprrel,	ktrans,	ktrans,
	// right thumb
	lpop3,	ktrans,
	ktrans,	NULL,	NULL,
	ktrans,	ktrans,	ktrans
),
// LAYER 3
KB_MATRIX_LAYER(
	// unused
	NULL,
	// left hand
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	// left thumb
		kprrel,	llsticky2,
	NULL,	NULL,	kprrel,
	kprrel,	kprrel,	kprrel,
	// right hand
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
		kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	// right thumb
	llsticky1,	kprrel,
	kprrel,	NULL,	NULL,
	kprrel,	kprrel,	kprrel
),
// LAYER 4
KB_MATRIX_LAYER(
	// unused
	NULL,
	// left hand
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,
	// left thumb
		NULL,	NULL,
	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,
	// right hand
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
		NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,
	// right thumb
	NULL,	NULL,
	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL
),
// LAYER 5
KB_MATRIX_LAYER(
	// unused
	NULL,
	// left hand
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,
	// left thumb
		NULL,	NULL,
	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,
	// right hand
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
		NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,
	// right thumb
	NULL,	NULL,
	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL
),
// LAYER 6
KB_MATRIX_LAYER(
	// unused
	NULL,
	// left hand
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,
	// left thumb
		NULL,	NULL,
	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,
	// right hand
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
		NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,
	// right thumb
	NULL,	NULL,
	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL
),
// LAYER 7
KB_MATRIX_LAYER(
	// unused
	NULL,
	// left hand
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,
	// left thumb
		NULL,	NULL,
	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,
	// right hand
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
		NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,
	// right thumb
	NULL,	NULL,
	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL
),
// LAYER 8
KB_MATRIX_LAYER(
	// unused
	NULL,
	// left hand
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,
	// left thumb
		NULL,	NULL,
	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,
	// right hand
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
		NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,
	// right thumb
	NULL,	NULL,
	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL
),
// LAYER 9
KB_MATRIX_LAYER(
	// unused
	NULL,
	// left hand
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,
	// left thumb
		NULL,	NULL,
	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,
	// right hand
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
		NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,
	// right thumb
	NULL,	NULL,
	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL
),
};
// ----------------------------------------------------------------------------

// RELEASE --------------------------------------------------------------------
const void_funptr_t PROGMEM _kb_layout_release[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {
// LAYER 0
KB_MATRIX_LAYER(
	// unused
	NULL,
	// left hand
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	// left thumb
		kprrel,	llsticky2,
	NULL,	NULL,	kprrel,
	kprrel,	kprrel,	kprrel,
	// right hand
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
		kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	// right thumb
	llsticky1,	kprrel,
	kprrel,	NULL,	NULL,
	kprrel,	kprrel,	kprrel
),
// LAYER 1
KB_MATRIX_LAYER(
	// unused
	NULL,
	// left hand
	NULL,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	kprrel,	NULL,	NULL,	NULL,	NULL,	NULL,	ktrans,
	kprrel,	NULL,	NULL,	NULL,	NULL,	NULL,
	ktrans,	NULL,	kprrel,	kprrel,	kprrel,	NULL,	ktrans,
	ktrans,	ktrans,	kprrel,	kprrel,	kprrel,
	// left thumb
		ktrans,	NULL,
	NULL,	NULL,	ktrans,
	ktrans,	ktrans,	ktrans,
	// right hand
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	ktrans,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
		NULL,	NULL,	NULL,	NULL,	NULL,	ktrans,
	ktrans,	NULL,	NULL,	NULL,	NULL,	NULL,	ktrans,
	kprrel,	kprrel,	kprrel,	ktrans,	kprrel,
	// right thumb
	NULL,	ktrans,
	ktrans,	NULL,	NULL,
	ktrans,	ktrans,	ktrans
),
// LAYER 2
KB_MATRIX_LAYER(
	// unused
	NULL,
	// left hand
	NULL,	NULL,	NULL,	kprrel,	kprrel,	NULL,	ktrans,
	ktrans,	NULL,	kprrel,	kprrel,	kprrel,	NULL,	ktrans,
	ktrans,	NULL,	kprrel,	NULL,	kprrel,	NULL,
	ktrans,	NULL,	kprrel,	kprrel,	kprrel,	NULL,	ktrans,
	ktrans,	ktrans,	ktrans,	kprrel,	kprrel,
	// left thumb
		ktrans,	NULL,
	NULL,	NULL,	ktrans,
	ktrans,	ktrans,	ktrans,
	// right hand
	ktrans,	NULL,	kprrel,	kprrel,	kprrel,	kprrel,	NULL,
	ktrans,	NULL,	kprrel,	kprrel,	kprrel,	kprrel,	NULL,
		NULL,	kprrel,	kprrel,	kprrel,	kprrel,	ktrans,
	ktrans,	NULL,	kprrel,	kprrel,	kprrel,	kprrel,	ktrans,
	kprrel,	kprrel,	kprrel,	ktrans,	ktrans,
	// right thumb
	NULL,	ktrans,
	ktrans,	NULL,	NULL,
	ktrans,	ktrans,	ktrans
),
// LAYER 3
KB_MATRIX_LAYER(
	// unused
	NULL,
	// left hand
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	// left thumb
		kprrel,	llsticky2,
	NULL,	NULL,	kprrel,
	kprrel,	kprrel,	kprrel,
	// right hand
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
		kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	kprrel,	kprrel,	kprrel,	kprrel,	kprrel,
	// right thumb
	llsticky1,	kprrel,
	kprrel,	NULL,	NULL,
	kprrel,	kprrel,	kprrel
),
// LAYER 4
KB_MATRIX_LAYER(
	// unused
	NULL,
	// left hand
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,
	// left thumb
		NULL,	NULL,
	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,
	// right hand
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
		NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,
	// right thumb
	NULL,	NULL,
	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL
),
// LAYER 5
KB_MATRIX_LAYER(
	// unused
	NULL,
	// left hand
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,
	// left thumb
		NULL,	NULL,
	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,
	// right hand
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
		NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,
	// right thumb
	NULL,	NULL,
	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL
),
// LAYER 6
KB_MATRIX_LAYER(
	// unused
	NULL,
	// left hand
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,
	// left thumb
		NULL,	NULL,
	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,
	// right hand
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
		NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,
	// right thumb
	NULL,	NULL,
	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL
),
// LAYER 7
KB_MATRIX_LAYER(
	// unused
	NULL,
	// left hand
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,
	// left thumb
		NULL,	NULL,
	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,
	// right hand
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
		NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,
	// right thumb
	NULL,	NULL,
	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL
),
// LAYER 8
KB_MATRIX_LAYER(
	// unused
	NULL,
	// left hand
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,
	// left thumb
		NULL,	NULL,
	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,
	// right hand
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
		NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,
	// right thumb
	NULL,	NULL,
	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL
),
// LAYER 9
KB_MATRIX_LAYER(
	// unused
	NULL,
	// left hand
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,
	// left thumb
		NULL,	NULL,
	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,
	// right hand
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
		NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,
	// right thumb
	NULL,	NULL,
	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL
),
};
// ----------------------------------------------------------------------------
