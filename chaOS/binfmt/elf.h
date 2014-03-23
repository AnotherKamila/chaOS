#ifndef BINFMT_ELF_H
#define BINFMT_ELF_H


#include "binfmt/common.h"
#include "util/mem.h"

#define TO_ADDR    (RAM_BASE + 0x200)


#define E_NOT_ELF_X       1
#define E_NOT_COMPATIBLE  2

typedef uintptr_t elf32_addr;   // unsigned address
typedef size_t    elf32_off;    // unsigned 4-byte integer
typedef uint16_t  elf32_half;   // unsigned 2-byte integer
typedef uint32_t  elf32_word;   // unsigned 4-byte integer
typedef int32_t   elf32_sword;  // signed 4-byte integer
typedef uint8_t   elf32_byte;   // unsigned byte

typedef struct {
    elf32_byte e_ident[16];  // machine-independent identification info
    elf32_half e_type;       // object file type
    elf32_half e_machine;    // architecture
    elf32_word e_version;    // object file standard version
    elf32_addr e_entry;      // entry point
    elf32_off  e_phoff;      // program header table's offset
    elf32_off  e_shoff;      // section header table's offset
    elf32_word e_flags;      // processor-specific flags
    elf32_half e_ehsize;     // ELF header size
    elf32_half e_phentsize;  // program header entry size (all program headers are the same size)
    elf32_half e_phnum;      // number of entries in the program header table
    elf32_half e_shentsize;  // section header entry size (all section headers are the same size)
    elf32_half e_shnum;      // number of entries in the section header table
    elf32_half e_shstrndx;   // ??? (TODO)
} ELF32_hdr;
#define EID0        0x7f
#define EC_32       1
#define ET_EXEC     2
#define EV_CURRENT  1
#define EM_ARM      0x28

typedef struct {
    elf32_word sh_name;       // index into the section name string table
    elf32_word sh_type;
    elf32_word sh_flags;
    elf32_addr sh_addr;       // address in the memory image that this should appear at
    elf32_off  sh_offset;     // offset from the file start to the section
    elf32_word sh_size;       // section size (in file, unless it is type SH_NOBITS - like .bss)
    elf32_word sh_link;       // type-dependent
    elf32_word sh_info;       // type-dependent
    elf32_word sh_addralign;  // alignment constraints (sh_addr needs to be a multiple of this)
    elf32_word sh_entsize;    // if it is a table of fixed-size entries, then this is the entry size
} ELF32_shdr;

enum sh_type {
    SHT_NULL     = 0,  // UNDEF
    SHT_PROGBITS = 1,  // program info
    SHT_SYMTAB   = 2,  // symbol table
    SHT_STRTAB   = 3,  // string table
    SHT_RELA     = 4,  // relocation (with addend)
    SHT_NOBITS   = 8,  // not present in the file
    SHT_REL      = 9,  // relocation (no addend)
};
enum sh_attributes {
    SHF_WRITE = 0x1,
    SHF_ALLOC = 0x2,
    SHF_EXEC  = 0x4,
};

static bool is_elf_x(ELF32_hdr *hdr) {
    return hdr->e_ident[0] == EID0 && hdr->e_type == ET_EXEC;
}
static bool is_compatible(ELF32_hdr *hdr) {
    return hdr->e_ident[4] == EC_32      &&
           hdr->e_version  == EV_CURRENT &&
           hdr->e_machine  == EM_ARM;
}

// TODO load from something file-like
// TODO allocate memory instead of this :D
// Note: assuming that everything starts at address 0
static int load_elf(const program_img *prg, exec_img *res) {
    ELF32_hdr *hdr = (ELF32_hdr*)prg->img;
    if (!is_elf_x(hdr))
        return E_NOT_ELF_X;
    if (!is_compatible(hdr))
        return E_NOT_COMPATIBLE;

    ELF32_shdr *sections = (ELF32_shdr*)((uintptr_t)hdr + hdr->e_shoff);

    // prepare .bss, load .text and .data
    for (int sec_idx = 0; sec_idx < hdr->e_shnum; ++sec_idx) {
        ELF32_shdr *shdr = &sections[sec_idx];
        if (shdr->sh_flags & SHF_ALLOC && shdr->sh_size) {  // non-empty allocatable sections
            uintptr_t addr = TO_ADDR + shdr->sh_addr;  // poor man's relocation :D (TODO of course it doesn't work)
            switch (shdr->sh_type) {
                case SHT_NOBITS:  // .bss
                    memset((void*)addr, 0, shdr->sh_size);
                    break;
                case SHT_PROGBITS:  // .data, .rodata and .text (should use FLAGS to set rwx access)
                    memcpy((void*)addr, (void*)((uintptr_t)prg->img + shdr->sh_offset), shdr->sh_size);
                    break;
            }
        }
    }

    res->entry = _tofunc(TO_ADDR + hdr->e_entry);  // traces of my poor man's relocation too
    return 0;
}


#endif
