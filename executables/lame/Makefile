MAIN      = lame.elf
CPU       = cortex-m0
LDSCRIPT  = ../chaos-executable.ld

# TODO should I (make and) use `arm-chaos-eabi-*`?
AS = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
SIZE=arm-none-eabi-size

ASFLAGS = -mcpu=$(CPU) -mthumb -g

LDFLAGS = -T$(LDSCRIPT) -nostdlib -nostartupfiles

# --------------------------------------------------------

default: $(MAIN)

$(MAIN): $(MAIN:.elf=.o)
	$(LD) $(LDFLAGS) -o $@ $<
	$(OBJCOPY) --strip-all -R .ARM.attributes $@
	$(SIZE) $(MAIN)

%.o: %.s
	$(AS) -c $(ASFLAGS) $< -o $@
