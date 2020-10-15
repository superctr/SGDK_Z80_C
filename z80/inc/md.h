#ifndef MD_H
#define MD_H

/* typedefs */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned long u32;
typedef signed long s32;

typedef volatile u8 vu8;
typedef volatile s8 vs8;
typedef volatile u16 vu16;
typedef volatile s16 vs16;
typedef volatile u32 vu32;
typedef volatile s32 vs32;

/* FM register */
__at (0x4000) vu8 FM_STATUS;
__at (0x4000) vu8 FM1_SELECT;
__at (0x4001) vu8 FM1_DATA;
__at (0x4002) vu8 FM2_SELECT;
__at (0x4003) vu8 FM2_DATA;

/* PSG register */
__at (0x6000) vu8 BANK_SELECT;
__at (0x7F11) vu8 PSG;

/* VDP vertical counter */
__at (0x7F08) vu8 VCOUNTER;

extern u8 current_bank;

//! Switch to the specified bank
inline void switch_bank(u8 new_bank)
{
	if(new_bank == current_bank)
		return;
	current_bank = new_bank;
	BANK_SELECT = new_bank; new_bank >>= 1;
	BANK_SELECT = new_bank; new_bank >>= 1;
	BANK_SELECT = new_bank; new_bank >>= 1;
	BANK_SELECT = new_bank; new_bank >>= 1;
	BANK_SELECT = new_bank; new_bank >>= 1;
	BANK_SELECT = new_bank; new_bank >>= 1;
	BANK_SELECT = new_bank; new_bank >>= 1;
	BANK_SELECT = new_bank;
	BANK_SELECT = 0;
}

//! Switch to next bank
void next_bank();

//! Convert a 68K address to Z80 bank number
inline u8 convert_bank(u32 addr)
{
	return addr >> 15;
}

//! Convert a 68K address to Z80 bank address
inline void* convert_addr(u32 addr)
{
	return (void*)(addr | 0x8000);
}

//! Increment address within bank area.
/*!
 *  If out of bounds, bank is automatically incremented
 */
inline void* inc_addr(void* addr, u8 inc)
{
	u16 out = (u16)addr + inc;
	if(out < 0x8000)
	{
		out |= 0x8000;
		next_bank();
	}
	return (void*) out;
}

#endif
