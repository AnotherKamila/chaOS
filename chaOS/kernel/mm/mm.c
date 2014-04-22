/**
 * my stupid little malloc implementation
 *
 * strategy:        best fit w/ adjacent free blocks merging
 * implementation:  linked list, 4-byte header: 1-bit full flag, 31-bit offset for this/previous
 *                  block), allocating in multiples of 4 bytes (therefore it can handle at most
 *                  2^31 = 2GB memory, but starting at any offset)
 * time complexity: malloc in O(N) where N is the number of all blocks; free in O(1)
 */

#include "kernel/panic.h"

#include "mm.h"

/* === kmalloc/kfree ============================================================================ */

#define UNIT      4u // smallest allocation unit (4 bytes)
#define ALIGN(x)  ((x+(UNIT-1)) & ~(UNIT-1)) // round up to the nearest multiple of 4

typedef uint32_t moff_t;
#define MHDR_SZ   ((moff_t)(sizeof (mhdr_t)))
#define FULLBIT   ((moff_t)(1u<<31))
#define SIZEBITS  ((moff_t)(FULLBIT-1))

extern const byte _kernel_end;  // linker-supplied address -- end of static kernel structures in RAM
extern const byte _stack_limit; // linker-supplied address -- above there be dragons (eh, stack)
#define mem_start  ((size_t)(&_kernel_end)) // start of managed memory
#define mem_size   ((moff_t)(&_stack_limit - &_kernel_end)) // size of managed memory

typedef uint32_t* mhdr_t;
intern mhdr_t hdr_at(const moff_t addr) { return (uint32_t*)(mem_start + addr); }

intern void set_full(mhdr_t h) { *h |= FULLBIT; }
intern void set_free(mhdr_t h) { *h &= ~FULLBIT; }
intern void set_size(mhdr_t h, moff_t sz) { kassert(sz <= SIZEBITS); *h &= ~SIZEBITS; *h |= sz; }
intern bool   is_full (const mhdr_t h) { return *h & FULLBIT;  }
intern moff_t get_size(const mhdr_t h) { return *h & SIZEBITS; }

intern void mk_free_block(const moff_t start, const moff_t end) {
    mhdr_t h = hdr_at(start);
    set_free(h); set_size(h, end - start - MHDR_SZ);
}

intern bool is_fragmented_at(moff_t addr) {
    const mhdr_t h = hdr_at(addr);
    return !is_full(h) &&
           addr + MHDR_SZ + get_size(h) < mem_size &&
           !is_full(hdr_at(addr + MHDR_SZ + get_size(h)));
}

// actually O(1) if everything works, as no more than 3 consecutive free blocks should occur
intern void defrag_at(const moff_t start) {
    moff_t curr = start;
    while (curr < mem_size && !is_full(hdr_at(curr))) {
        curr += MHDR_SZ + get_size(hdr_at(curr));
    }
    mk_free_block(start, curr);
}

void *kmalloc(size_t sz) {
    if (sz == 0) return NULL;
    moff_t size = ALIGN(sz);

    // find the best fitting free block
    moff_t best_addr;
    moff_t best_size = 0;
    moff_t curr = 0;
    while (curr < mem_size) {
        mhdr_t h = hdr_at(curr);

        if (is_fragmented_at(curr)) defrag_at(curr);

        if (!is_full(h) && get_size(h) >= size) { // we only want free blocks that are big enough
            if (!best_size || get_size(h) < best_size) {
                best_size = get_size(h);
                best_addr = curr;
            }
        }
        curr += MHDR_SZ + get_size(h);
    }
    if (!best_size) return NULL; // no free block was big enough

    if (best_size - size <= MHDR_SZ) {
        // then we need to allocate more, because a block does not fit between this and the next one
        size = best_size;
    }

    mhdr_t h = hdr_at(best_addr); set_size(h, size); set_full(h);
    if (size != best_size) { // then there is a new free block
        mk_free_block(best_addr + MHDR_SZ + size, best_addr + MHDR_SZ + best_size);
    }

    return (void*)(mem_start + best_addr + MHDR_SZ);
}

void kfree(void *ptr) {
    if (ptr == NULL) return; // just ignore NULL

    const moff_t blockbeg = (size_t)ptr - mem_start - MHDR_SZ;
    mhdr_t h = hdr_at(blockbeg);
    kassert(is_full(h));
    set_free(h);
}

/* === mm_init -- memory management subsystem initialization routine ============================ */

void mm_init(void) {
    // needed by kmalloc/kfree
    mk_free_block(0, mem_size); // create a single free block spanning all memory
}
