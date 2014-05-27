TO_ADDR_G   = 0x8008000
TO_ADDR_B   = 0x8009000
TO_ADDR_OFF = 0x800A000

CPU       = cortex-m0
LDSCRIPT  = ../chaos-executable.ld

# TODO should I (make and) use `arm-chaos-eabi-*`?
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
SIZE=arm-none-eabi-size

CFLAGS  = -mcpu=$(CPU) -mthumb -g -std=c11 -W -Wall -pedantic
CFLAGS += -fpie

LDFLAGS  = -T$(LDSCRIPT) -nostdlib -nostartupfiles
LDFLAGS += -pie

# --------------------------------------------------------

default: green.elf blue.elf off.elf

%.elf: %.o
	$(LD) $(LDFLAGS) -o $@ $<
	# $(OBJCOPY) --strip-all -R .ARM.attributes $@
	$(OBJCOPY) --strip-debug -R .ARM.attributes $@
	$(SIZE) $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

flash: on.elf off.elf
	st-flash write green.elf  $(TO_ADDR_G)
	st-flash write blue.elf   $(TO_ADDR_B)
	st-flash write off.elf    $(TO_ADDR_OFF)
