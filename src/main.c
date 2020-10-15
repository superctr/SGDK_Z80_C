#include <genesis.h>
#include "z80drv.h"

#define Z80_INIT_FLAG 0xA0000F
#define Z80_PLAY_ADDR 0xA00010
#define Z80_PLAY_FLAG 0xA00014

// Test register data to be played
static const u8 fm_test[] =
{
	0x22, 0x00, // LFO off
	0x27, 0x00, // CH3 mode normal

	0x28, 0x00, // ch 0 off
	0x28, 0x01, // ch 1 off
	0x28, 0x02, // ch 2 off
	0x28, 0x04, // ch 3 off
	0x28, 0x05, // ch 4 off
	0x28, 0x06, // ch 5 off

	0x2B, 0x00, // DAC off

	0x30, 0x71, 0x34, 0x0d, 0x38, 0x33, 0x3c, 0x01, // DT1/MUL
	0x40, 0x23, 0x44, 0x2d, 0x48, 0x26, 0x4c, 0x00, // Total Level
	0x50, 0x5f, 0x54, 0x99, 0x58, 0x5f, 0x5c, 0x94, // RS/AR
	0x60, 0x05, 0x64, 0x05, 0x68, 0x05, 0x6c, 0x07, // AM/D1R
	0x70, 0x02, 0x74, 0x02, 0x78, 0x02, 0x7c, 0x02, // D2R
	0x80, 0x11, 0x84, 0x11, 0x88, 0x11, 0x8c, 0xa6, // D1L/RR
	0x90, 0x00, 0x94, 0x00, 0x98, 0x00, 0x9c, 0x00, // SSG-EG

	0xb0, 0x32, // Feedback / algorithm
	0xb4, 0xc0, // Both speakers on
	0x28, 0x00, // Key off
	0xa4, 0x22, // Set frequency
	0xa0, 0x69,
	0x28, 0xf0, // Key on

	0x00, 0x00
};

// Wait until our custom Z80 driver is initialized (byte at 0x000f is 0)
void wait_z80()
{
	u32 tmp;
	vu8* init_flag = (u8*) Z80_INIT_FLAG;
	while(TRUE)
	{
		Z80_requestBus(TRUE);
		if(!(*init_flag))
			break;
		Z80_releaseBus();

		// waste some cycles
        asm volatile (
        "moveq #7,%0\n"
        "1:\n\t"
        "\tdbra %0,1b\n\t"
        : "=d" (tmp) : : "cc"
        );
	}
	Z80_releaseBus();
}

// Tell our custom Z80 driver to play the above register data
void play_z80()
{
	Z80_requestBus(TRUE);

	u32 play_addr = (u32)fm_test;

	vu8* z80_addr = (u8*) Z80_PLAY_ADDR;
	
	*z80_addr++ = play_addr;
	*z80_addr++ = play_addr >> 8;
	*z80_addr++ = play_addr >> 16;
	*z80_addr++ = play_addr >> 24;
	*z80_addr = 0xff;

	Z80_releaseBus();
}

int main(u16 hard)
{
	JOY_init();
	Z80_loadCustomDriver(z80drv, sizeof(z80drv));

	VDP_drawText("Z80 custom driver test!", 4, 2);

	wait_z80();
	play_z80();

	return 0;
}
