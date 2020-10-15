# Z80 integration for SGDK
This is an example project using SDCC to build a Z80 sound driver
that can be linked with the SGDK.

The example code uses the Z80 to read some YM2612 commands from the ROM,
using bank switching.

Keep in mind that SDCC doesn't generate _fast_ Z80 assembly code, so
C code won't be very useful for sample playback.

## How to use
Currently this is only tested on windows.

1. Download the SGDK windows snapshot from [here](http://sdcc.sourceforge.net/snap.php#Windows)
2. Set the environment variable `SDCC_WIN` to point to the SDCC `bin` folder. Use Windows path separators.
3. Add the SDCC `bin` folder to the PATH environment variable.
4. `make`

## Notes
- 68K can halt Z80 when it is in the middle of reading stuff, so be careful
when transferring commands larger than a single byte.
- Keep in mind that the YM2612 requires a minimum waiting period between register writes, and between address and register writes.
- As a rule of thumb, around 50 Z80 cycles are needed between register writes, and 15 cycles between register and address. SDCC generates assembly listings (containing cycle counts) in `z80/obj`, check there for details.
- Add nops as necessary (using inlined ASM) in the unlikely case that SDCC manages to generate code that violates the above timing rule.
- Use fixed addresses in Z80 space for communication with the 68k. On the 68k side, use `#define`s and volatile pointers to read/write Z80 memory, and on the Z80 side, use the `__at (address)` to directly specify an address for a variable.
- Make sure all your Z80 code and variables fit in 8kb of memory. Initialized variables take twice the amount of space.

## Credits
By Ian Karlsson.

All code is released in the public domain, feel free to use as you wish.
