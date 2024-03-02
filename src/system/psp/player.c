#include <pspkernel.h>
#include <psprtc.h>

#include <stdio.h>

#include <tic80.h>

#include "input.h"
#include "gu.h"

#define TIC80_DEFAULT_CART "cart.tic"

PSP_MODULE_INFO("TIC-80", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER | PSP_THREAD_ATTR_VFPU);

static tic80* tic = NULL;
static tic80_input tic_input;

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

void main() {
    FILE* file = fopen(TIC80_DEFAULT_CART, "rb");

    if(file)
    {
        fseek(file, 0, SEEK_END);
        int size = ftell(file);
        fseek(file, 0, SEEK_SET);

        void* cart = malloc(size);
        if(cart) fread(cart, size, 1, file);
        fclose(file);

        if(cart)
        {
            printf("cart read, creating tic\n");
            tic = tic80_create(0, TIC80_PIXEL_COLOR_RGBA8888);

            if(tic)
            {
                printf("tic created, loading cart\n");
                tic80_load(tic, cart, size);
            }
        }
    }

    psp_gu_init();

    while (1) {
        psp_gu_start_frame();

		psp_gamepad_update(&tic_input);

        tic80_tick(tic, tic_input, tic_sys_counter_get, tic_sys_freq_get);

        psp_gu_draw_frame(tic->screen);

        psp_gu_end_frame();
    }

    sceKernelExitGame();
}

// stub because it complained
#include <sys/types.h>
int ftruncate(int fd, off_t length)
{
	return -1;
}
