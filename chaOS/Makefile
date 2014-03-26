MAIN      = main.elf
CPU       = cortex-m0
LDSCRIPT  = device/stm32f0.ld

CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
SIZE=arm-none-eabi-size

CFLAGS  = -std=c11 -lm -W -Wall -Wextra -pedantic
CFLAGS += -mcpu=$(CPU) -mthumb
CFLAGS += -O2 -ffunction-sections -fdata-sections
CFLAGS += -I. -I../cslibc/inc
DEBUG_CFLAGS = -DDEBUG -g3 -O0

LDFLAGS  = -T$(LDSCRIPT) -nostdlib -nostartupfiles
LDFLAGS += --gc-sections

SRCS = $(shell find -name '*.c')
OBJS = $(SRCS:.c=.o)
LIBSRCS = $(shell find ../cslibc/ -name '*.c')
LIBOBJS = $(LIBSRCS:.c=.o)

# --------------------------------------------------------

ifeq ($(NODEBUG),)
	CFLAGS += $(DEBUG_CFLAGS)
endif

# --------------------------------------------------------

default: $(MAIN)

$(MAIN): $(OBJS) $(LIBOBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LIBOBJS)
	$(SIZE) $(MAIN)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
	$(CC) -MM $(CFLAGS) $< > $*.d

%.o: %.s
	$(CC) -c $(CFLAGS) $< -o $@

gdb: $(MAIN)
	arm-none-eabi-gdb --command=.gdb-startup $(MAIN)

.PHONY: clean

clean:
	find . -name '*.[od]' -exec rm -f '{}' \;
	rm -f *.elf
