# changing these (and of course adding MCU-specific ld and header files) allows recompilation for
# various processors -- theoretically any ARM should work, but I have not tested anything other
# than my STM32F0 board
FAMILY = cortex-m0
MCU    = stm32f0
BOARD  = discovery-f0

MAIN     = chaos.elf
LDSCRIPT = mcus/$(FAMILY)/$(MCU)/device.ld

CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
SIZE=arm-none-eabi-size

CFLAGS  = -std=c11 -lm -W -Wall -Wextra -pedantic
CFLAGS += -mcpu=$(FAMILY) -mthumb -ffreestanding
CFLAGS += -O2 -ffunction-sections -fdata-sections
CFLAGS += -DCHAOS_KERNEL -I. -I../cslibc/inc
DEBUG_CFLAGS = -g3 -O0

LDFLAGS  = -T$(LDSCRIPT) -nostdlib -nodefaultlibs -nostartupfiles
LDFLAGS += --gc-sections

CFLAGS += -DCPU=$(MCU)       -I "mcus/$(FAMILY)/$(MCU)"
CFLAGS += -DFAMILY=$(FAMILY) -I "mcus/$(FAMILY)/common"
CFLAGS += -DBOARD=$(BOARD)   -I "boards/$(BOARD)"

SRCS  = $(shell find \( -path ./mcus -o -path ./boards \) -prune -o -name '*.c' -print)
SRCS += $(shell find mcus/$(FAMILY)/$(MCU) -name '*.c')
SRCS += $(shell find mcus/$(FAMILY)/common -name '*.c')
SRCS += $(shell find boards/$(BOARD) -name '*.c')

OBJS    = $(SRCS:.c=.o)
LIBSRCS = $(shell find ../cslibc/ -name '*.c')
LIBOBJS = $(LIBSRCS:.c=.o)

# --------------------------------------------------------------------------------------------------

ifeq ($(NODEBUG),)
	CFLAGS += $(DEBUG_CFLAGS)
else
	CFLAGS += -DNDEBUG
endif

# --------------------------------------------------------------------------------------------------

default: $(MAIN)

$(MAIN): $(OBJS) $(LIBOBJS)
	$(LD) $(LDFLAGS) -o $@ $+
	$(SIZE) $(MAIN)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
	$(CC) -MM $(CFLAGS) $< > $*.d

gdb: $(MAIN)
	arm-none-eabi-gdb --command=.gdb-startup $(MAIN)

.PHONY: clean

clean:
	find . -name '*.[od]' -exec rm -f '{}' \;
	rm -f *.elf

# include the generated dependencies
-include $(OBJS:.o=.d)
