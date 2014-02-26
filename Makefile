ELF       = main.elf
CPU       = cortex-m0
LDSCRIPT  = device/stm32f0.ld

CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
SIZE=arm-none-eabi-size

CFLAGS  = -lm -W -Wall -Wextra -O2
CFLAGS += -mcpu=$(CPU) -mthumb

LDFLAGS = -T$(LDSCRIPT) -nostartupfiles

DEBUG_CFLAGS = -g3 -O0

SRCS = $(wildcard *.c) $(wildcard **/*.c)
OBJS = $(SRCS:.c=.o)

# --------------------------------------------------------

ifeq ($(DEBUG), 1)
	CFLAGS += $(DEBUG_CFLAGS)
endif

# --------------------------------------------------------

default: $(ELF)

$(ELF): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)
	$(SIZE) $(ELF)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
	$(CC) -MM $(CFLAGS) $< > $*.d

%.o: %.s
	$(CC) -c $(CFLAGS) $< -o $@

gdb: $(ELF)
	arm-none-eabi-gdb --command=.gdb-startup $(ELF)
