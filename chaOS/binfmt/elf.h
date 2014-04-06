#ifndef _BINFMT_ELF_H
#define _BINFMT_ELF_H


#include "string.h"
#include "devices/core.h"
#include "binfmt/common.h"

#define TO_ADDR  (RAM_BASE + 0x200)  // TODO

#define E_NOT_ELF_X       1
#define E_NOT_COMPATIBLE  2

typedef uint32_t elf32_addr;   // unsigned address
typedef uint32_t elf32_off;    // unsigned 4-byte integer
typedef uint16_t elf32_half;   // unsigned 2-byte integer
typedef uint32_t elf32_word;   // unsigned 4-byte integer
typedef int32_t  elf32_sword;  // signed 4-byte integer
typedef uint8_t  elf32_byte;   // unsigned byte

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
    elf32_half e_shstrndx;   // string table section index
} ELF32_hdr;
#define EID0        0x7f  // ELF format magic number
#define EV_CURRENT  1     // ELF format version
#define EC_32       1     // 32-bit arch
#define EM_ARM      0x28  // for ARM CPUs
#define ET_EXEC     2     // type: normal executable
#define ET_DYN      3     // type: PIE (or a shared library, but shared libraries are useless now)

typedef struct {
    elf32_word sh_name;       // index into the section name string table
    elf32_word sh_type;
    elf32_word sh_flags;
    elf32_addr sh_addr;       // address in the memory image that this should appear at
    elf32_off  sh_off;        // offset from the file start to the section
    elf32_word sh_size;       // section size (in file, unless it is type SH_NOBITS - like .bss)
    elf32_word sh_link;       // type-dependent
    elf32_word sh_info;       // type-dependent
    elf32_word sh_addralign;  // alignment constraints (sh_addr needs to be a multiple of this)
    elf32_word sh_entsize;    // if it is a table of fixed-size entries, then this is the entry size
} ELF32_shdr;

enum sh_type {
    SHT_NULL     =  0,  // UNDEF
    SHT_PROGBITS =  1,  // program info
    SHT_SYMTAB   =  2,  // symbol table
    SHT_STRTAB   =  3,  // string table
    SHT_RELA     =  4,  // relocation (with addend)
    SHT_HASH     =  5,  // symbol hash table
    SHT_DYNAMIC  =  6,  // info for dynamic linking
    SHT_NOTE     =  7,
    SHT_NOBITS   =  8,  // not present in the file
    SHT_REL      =  9,  // relocation (no addend)
    SHT_SHLIB    = 10,  // no specified semantics
    SHT_DYNSYM   = 11,  // dynamic symbols table
};
enum sh_flags {
    SHF_WRITE = 0x1,
    SHF_ALLOC = 0x2,
    SHF_EXEC  = 0x4,
};

static bool is_elf_x(ELF32_hdr *hdr) {
    return hdr->e_ident[0] == EID0 &&
           hdr->e_ident[1] == 'E'  &&
           hdr->e_ident[2] == 'L'  &&
           hdr->e_ident[3] == 'F'  &&
           (hdr->e_type == ET_EXEC || hdr->e_type == ET_DYN);
}
static bool is_compatible(ELF32_hdr *hdr) {
    return hdr->e_ident[4] == EC_32      &&
           hdr->e_version  == EV_CURRENT &&
           hdr->e_machine  == EM_ARM;
}

// TODO load from something file-like
static int load_elf(const program_img *prg, exec_img *res) {
    uintptr_t from_addr = (uintptr_t)prg->img;
    uintptr_t to_addr = TO_ADDR;  // TODO allocate memory instead of this :D
    // assuming my binary starts at 0x0
    ELF32_hdr *hdr = (ELF32_hdr*)prg->img;
    if (!is_elf_x(hdr))
        return E_NOT_ELF_X;
    if (!is_compatible(hdr))
        return E_NOT_COMPATIBLE;

    ELF32_shdr *sections = (ELF32_shdr*)((uintptr_t)hdr + hdr->e_shoff);
    char *strings = (char*)(from_addr + sections[hdr->e_shstrndx].sh_off);

    // prepare .bss, relocate GOT, load .text and .data
    for (int sec_idx = 0; sec_idx < hdr->e_shnum; ++sec_idx) {
        ELF32_shdr *shdr = &sections[sec_idx];
        if (shdr->sh_flags & SHF_ALLOC && shdr->sh_size) {  // non-empty allocatable sections
            uintptr_t daddr = to_addr + shdr->sh_addr;  // poor man's relocation :D
            char *name = strings + shdr->sh_name;
            if (memcmp(name, ".got", 4) == 0) {  // handle relocation -- copy adding offset
                // TODO assert that shdr->sh_entsize is 4 bytes
                uint32_t *src  = (uint32_t*)(from_addr + shdr->sh_off);
                uint32_t *dest = (uint32_t*)daddr;
                while ((uintptr_t)dest < (uint32_t)(daddr + shdr->sh_size))
                    *dest++ = to_addr + *src++;  // to_addr is also the offset (as start is at 0x0)
            }
            else {
                switch (shdr->sh_type) {
                    case SHT_NOBITS:  // .bss
                        memset((void*)daddr, 0, shdr->sh_size);
                        break;
                    case SHT_PROGBITS:  // .data, .rodata, .text (should use FLAGS to set rwx perms)
                        memcpy((void*)daddr, (void*)(from_addr + shdr->sh_off), shdr->sh_size);
                        break;
                }
            }
        }
    }

    res->entry = _tofunc(to_addr + hdr->e_entry);  // traces of my poor man's relocation too
    return 0;
}


#endif
