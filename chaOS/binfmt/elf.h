/* ELF executables support */

#ifndef BINFMT_ELF_H
#define BINFMT_ELF_H


#include "devices/core.h"
#include "binfmt/common.h"

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
    elf32_word sh_entsize;    // if it is a table of fixed-size entries, then this is that size
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

int load_elf(const program_img *prg, exec_img *res);


#endif
