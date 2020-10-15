; **********************************
; Mega Drive Z80 initialization code
; **********************************
	.module crt0

	.globl _main
	.globl _vint

	.area _HEADER (ABS)

; Entrypoint
	.org 0
	di
	im 1
	ld sp,#0x2000
	call gsinit
	call _main
1$:
	jr 1$

; Interrupt handler
	.org 0x38
	ex af,af'
	exx
	push ix
	push iy
	call _vint
	pop iy
	pop ix
	exx
	ex af,af'
	ret			; no need to reti on MD

; Section include order
	.area _HOME
	.area _CODE
	.area _INITIALIZER
	.area _GSINIT
	.area _GSFINAL
	.area _DATA
	.area _INITIALIZED
	.area _BSEG
	.area _BSS
	.area _HEAP

; Initializer
	.area _GSINIT
gsinit:
	ld bc,#l__INITIALIZER
	ld a,b
	or a,c
	jr z,gsnext
	ld de,#s__INITIALIZED
	ld hl,#s__INITIALIZER
	ldir
gsnext:

	.area _GSFINAL
	ret
