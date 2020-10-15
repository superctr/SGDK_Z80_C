#include "md.h"

// The memory is initialized to 0xff by the linker so we will
// set this to 0 once we are ready.
__at(0x000f) vu8 init_flag;

// playback address in 68k address space
__at(0x0010) vu32 play_addr;

// flag that play_addr is valid and 68k wants data to be played
__at(0x0014) vu8 play_flag;

// Play register data found in 68k bank
void play()
{
	switch_bank(convert_bank(play_addr));

	u8* ptr = convert_addr(play_addr);
	while(*ptr)
	{
		while(FM_STATUS & 0x80);
		FM1_SELECT = *ptr;
		ptr = inc_addr(ptr, 1);
		FM1_DATA = *ptr;
		ptr = inc_addr(ptr, 1);
	}
}

// Main entry
void main()
{
	play_flag = 0;
	play_addr = 0;
	init_flag = 0;

	while(1)
	{
		if(play_flag)
		{
			play_flag = 0;
			play();
		}
	}
}

// vblank entry
void vint()
{
}
