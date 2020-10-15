CC=sdcc
AS=sdasz80
LD=sdldz80

SRC=./src
OBJ=./obj
INC=./inc

CCFLAGS= -mz80 --std-c99 -I$(INC) --max-allocs-per-node 1000000 --opt-code-size
ASFLAGS= -plosgff
# LDFLAGS= -mz80 --no-std-crt0 --code-loc 0 --data-loc 0
LDFLAGS= -mjwx -b _CODE=0x0048 -k $(SDCC_WIN)/../lib/z80 -l z80

OUTPRG=$(OBJ)/z80prg
OUTPRG_BIN=$(OUTPRG).bin

# crt0.rel must be first object!
OBJS = \
	$(OBJ)/crt0.rel \
	$(OBJ)/md.rel \
	$(OBJ)/main.rel \

DEPEND = \
	$(INC)/md.h \

$(OUTPRG_BIN):	$(OBJS)
	$(LD) $(LDFLAGS) -i $(OUTPRG).ihx $(OBJS) -e
	makebin -s 8192 $(OUTPRG).ihx $(OUTPRG_BIN)

$(OBJ)/%.rel:	$(SRC)/%.c $(DEPEND)
	@mkdir -p $(@D)
	$(CC) $(CCFLAGS) -o $@ -c $<

$(OBJ)/%.rel:	$(SRC)/%.s
	@mkdir -p $(@D)
	$(AS) $(ASFLAGS) -o $@ $<

build: $(OUTPRG_BIN)

clean:
	rm -f $(OBJ)/*

cb: clean build

.PHONY: build clean cb
