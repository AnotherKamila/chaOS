/* memory management (right now only kmalloc/kfree) */

#ifndef KERNEL_MM_H
#define KERNEL_MM_H


#include "devices/core.h"

/**
 * initializes the memory management subsystem
 */
void mm_init(void);

/**
 * allocates `sz` bytes and returns a pointer to the allocated memory; returns NULL if the request
 * cannot be fulfilled
 *
 * O(N) -- needs to check all blocks, and also defragments along the way
 */
void* kmalloc(size_t size); // TODO add flags

/**
 * frees the memory at `ptr` if `ptr` is a valid pointer previously returned by `malloc` and not yet
 * freed; otherwise undefined behavior occurs
 *
 * O(1)
 */
void kfree(void *ptr);


#endif
