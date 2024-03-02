#include <pspkernel.h>
#include <pspdisplay.h>
#include <psprtc.h>
#include <pspge.h>
#include <pspgu.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>

#include "input.h"
#include "gu.h"

#include "studio/system.h"

PSP_MODULE_INFO("TIC-80", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER | PSP_THREAD_ATTR_VFPU);

static struct
{
    Studio* studio;
    tic80_input input;
    char* clipboard;
} platform;

u64 tic_sys_counter_get()
{
    u64 tick;
    sceRtcGetCurrentTick(&tick);
    return tick;
}

u64 tic_sys_freq_get()
{
    return sceRtcGetTickResolution();
}

void tic_sys_preseed()
{
    u64 tick;
    sceRtcGetCurrentTick(&tick);

    srand(tick);
    rand();
}

void tic_sys_clipboard_set(const char* text)
{
    if(platform.clipboard)
    {
        free(platform.clipboard);
        platform.clipboard = NULL;
    }

    platform.clipboard = strdup(text);
}

bool tic_sys_clipboard_has()
{
    return platform.clipboard != NULL;
}

char* tic_sys_clipboard_get()
{
    return platform.clipboard ? strdup(platform.clipboard) : NULL;
}

void tic_sys_clipboard_free(const char* text)
{
    free((void*) text);
}

void tic_sys_fullscreen_set(bool value)
{
}

bool tic_sys_fullscreen_get()
{
}

void tic_sys_message(const char* title, const char* message)
{
}

void tic_sys_title(const char* title)
{
}

void tic_sys_open_path(const char* path) {}
void tic_sys_open_url(const char* url) {}

void tic_sys_update_config()
{

}

void tic_sys_default_mapping(tic_mapping* mapping)
{
    *mapping = (tic_mapping)
    {
        tic_key_up,
        tic_key_down,
        tic_key_left,
        tic_key_right,

        tic_key_z, // a
        tic_key_x, // b
        tic_key_a, // x
        tic_key_s, // y
    };
}

bool tic_sys_keyboard_text(char* text)
{
    return false;
}

void psp_gu_studio_draw_frame() {
	u32 *in = studio_mem(platform.studio)->product.screen;
	psp_gu_draw_frame(in);
}

void main() {
    char *backup_argv[] = { "/PSP/GAMES/Emulators/Tic-80/EBOOT.PBP", 0 };
    int argc_used = 1;

	memset(&platform, 0, sizeof(platform));
   
    platform.studio = studio_create(argc_used, backup_argv, 0, TIC80_PIXEL_COLOR_RGBA8888, "./", INT32_MAX);


    psp_gu_init();
    printf("gu has been init'd\n");

    while (!studio_alive(platform.studio)) {
        psp_gu_start_frame();

		psp_gamepad_update(&platform.input);

		studio_tick(platform.studio, platform.input);

        psp_gu_studio_draw_frame();

        psp_gu_end_frame();
    }

    sceKernelExitGame();
}

#include <sys/types.h>
int ftruncate(int fd, off_t length)
{
	return -1;
}