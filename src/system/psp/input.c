#include <pspctrl.h>

#include <tic80.h>

SceCtrlData pad;

void psp_gamepad_update(tic80_input* input) {
    tic80_gamepads *tic_pad = &input->gamepads;
    tic80_mouse *tic_mouse = &input->mouse;

sceCtrlReadBufferPositive(&pad, 1);    
    // gamepad
	tic_pad->first.data = 0;
	tic_pad->first.up = (pad.Buttons & PSP_CTRL_UP) != 0;
	tic_pad->first.down = (pad.Buttons & PSP_CTRL_DOWN) != 0;
	tic_pad->first.left = (pad.Buttons & PSP_CTRL_DOWN) != 0;
	tic_pad->first.right = (pad.Buttons & PSP_CTRL_RIGHT) != 0;
	tic_pad->first.a = (pad.Buttons & PSP_CTRL_CROSS) != 0;
	tic_pad->first.b = (pad.Buttons & PSP_CTRL_CIRCLE) != 0;
	tic_pad->first.x = (pad.Buttons & PSP_CTRL_SQUARE) != 0;
	tic_pad->first.y = (pad.Buttons & PSP_CTRL_TRIANGLE) != 0;
}
