#include "md.h"

u8 current_bank = 0xff;

void next_bank()
{
	switch_bank(current_bank + 1);
}
