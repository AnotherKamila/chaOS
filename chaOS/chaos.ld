/* This file should be included into the device-specific one (which is
   referenced in the Makefile and contains the memory map - FLASH and RAM
   address ranges */

_estack = ORIGIN(RAM) + LENGTH(RAM);

_min_stack_sz = 256;
PROVIDE(_stack_limit = _estack - _min_stack_sz);

PROVIDE(_FLASH_BASE_L = ORIGIN(FLASH));
PROVIDE(_RAM_BASE_L   = ORIGIN(RAM));

SECTIONS {

    .text : {
        . = ALIGN(4);

        _stext = .;

        KEEP(*(.isr_vector))
        *(.text)
        *(.text.*)
        *(.rodata)
        *(.rodata.*)

        _etext = .;
        _sidata = _etext;
    } >FLASH

    .data : AT(_sidata) {
        . = ALIGN(4);

        _sdata = .;

        *(.data)
        *(.data.*)
        *(.RAMtext)

        _edata = .;
    } >RAM

    .bss : {
        . = ALIGN(4);

        _sbss = .;

        *(.bss)
        *(.bss.*)
        *(COMMON)

        _ebss = .;
    } >RAM

    /* --- Cause an error if there is not enough RAM left for the stack ----- */
    ._stack : {
        . += _min_stack_sz;
    } >RAM

    /* --- Debug info ------------------------------------------------------- */
    .stab          0 : { *(.stab) }
    .stabstr       0 : { *(.stabstr) }
    .stab.excl     0 : { *(.stab.excl) }
    .stab.exclstr  0 : { *(.stab.exclstr) }
    .stab.index    0 : { *(.stab.index) }
    .stab.indexstr 0 : { *(.stab.indexstr) }
    .comment       0 : { *(.comment) }
    /* DWARF debug sections.
       Symbols in the DWARF debugging sections are relative to the beginning
       of the section so we begin them at 0.  */
    /* DWARF 1 */
    .debug          0 : { *(.debug) }
    .line           0 : { *(.line) }
    /* GNU DWARF 1 extensions */
    .debug_srcinfo  0 : { *(.debug_srcinfo) }
    .debug_sfnames  0 : { *(.debug_sfnames) }
    /* DWARF 1.1 and DWARF 2 */
    .debug_aranges  0 : { *(.debug_aranges) }
    .debug_pubnames 0 : { *(.debug_pubnames) }
    /* DWARF 2 */
    .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
    .debug_abbrev   0 : { *(.debug_abbrev) }
    .debug_line     0 : { *(.debug_line) }
    .debug_frame    0 : { *(.debug_frame) }
    .debug_str      0 : { *(.debug_str) }
    .debug_loc      0 : { *(.debug_loc) }
    .debug_macinfo  0 : { *(.debug_macinfo) }
    /* SGI/MIPS DWARF 2 extensions */
    .debug_weaknames 0 : { *(.debug_weaknames) }
    .debug_funcnames 0 : { *(.debug_funcnames) }
    .debug_typenames 0 : { *(.debug_typenames) }
    .debug_varnames  0 : { *(.debug_varnames) }
}
