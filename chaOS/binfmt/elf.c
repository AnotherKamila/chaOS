#include "elf.h"
#include "binfmt/common.h"
#include "kernel/mm/mm.h"
#include "string.h"
#include "util/bit_manip.h"

intern bool is_elf_x(ELF32_hdr *hdr) {
    return hdr->e_ident[0] == EID0 &&
           hdr->e_ident[1] == 'E'  &&
           hdr->e_ident[2] == 'L'  &&
           hdr->e_ident[3] == 'F'  &&
           (hdr->e_type == ET_EXEC || hdr->e_type == ET_DYN);
}
intern bool is_compatible(ELF32_hdr *hdr) {
    return hdr->e_ident[4] == EC_32      &&
           hdr->e_version  == EV_CURRENT &&
           hdr->e_machine  == EM_ARM;
}

// TODO load from something file-like
int load_elf(const program_img *prg, exec_img *res) {
    // note: I am assuming my binary starts at 0x0 throughout this function
    const uintptr_t from_addr = (uintptr_t)prg->img; // TODO this should read a file one day
    ELF32_hdr *hdr = (ELF32_hdr*)prg->img;
    if (!is_elf_x(hdr)) {
        return E_NOT_ELF_X;
    }
    if (!is_compatible(hdr)) {
        return E_NOT_COMPATIBLE;
    }

    ELF32_shdr *sections = (ELF32_shdr*)((uintptr_t)hdr + hdr->e_shoff);
    char *strings = (char*)(from_addr + sections[hdr->e_shstrndx].sh_off);

    // pass 1: just find out the future executable image's size and allocate memory
    size_t size = 0;
    for (int sec_idx = 0; sec_idx < hdr->e_shnum; ++sec_idx) {
        ELF32_shdr *shdr = &sections[sec_idx];
        if (shdr->sh_flags & SHF_ALLOC && shdr->sh_size) { // non-empty allocatable sections
            // sh_size needs to be aligned according to the next section's addralign, as that will
            // start aligned and therefore any holes created by the alignment must be accounted for
            const int align = (sec_idx+1 < hdr->e_shnum) ? (&sections[sec_idx+1])->sh_addralign : 1;
            size += ALIGN(align, shdr->sh_size);
        }
    }
    const uintptr_t to_addr = (uintptr_t)kmalloc(size);
    res->start = (void*)to_addr; res->end = (void*)(to_addr + size);

    // pass 2: relocate GOT, prepare .bss, load .text and .data
    for (int sec_idx = 0; sec_idx < hdr->e_shnum; ++sec_idx) {
        ELF32_shdr *shdr = &sections[sec_idx];
        if (shdr->sh_flags & SHF_ALLOC && shdr->sh_size) { // non-empty allocatable sections
            uintptr_t daddr = to_addr + shdr->sh_addr; // poor man's relocation :D
            char *name = strings + shdr->sh_name;
            if (memcmp(name, ".got", 4) == 0) { // handle relocation -- copy adding offset
                // TODO assert that shdr->sh_entsize is 4 bytes
                uint32_t *src  = (uint32_t*)(from_addr + shdr->sh_off);
                uint32_t *dest = (uint32_t*)daddr;
                while ((uintptr_t)dest < (uint32_t)(daddr + shdr->sh_size)) {
                    *dest++ = to_addr + *src++; // to_addr is also the offset (as start is at 0x0)
                }
            }
            else {
                switch (shdr->sh_type) {
                    case SHT_NOBITS: // .bss
                        memset((void*)daddr, 0, shdr->sh_size);
                        break;
                    case SHT_PROGBITS: // .data, .rodata, .text (should use FLAGS to set rwx perms)
                        memcpy((void*)daddr, (void*)(from_addr + shdr->sh_off), shdr->sh_size);
                        break;
                }
            }
        }
    }

    res->entry = _tofunc(to_addr + hdr->e_entry);
    return 0;
}
