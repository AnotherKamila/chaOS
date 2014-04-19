/* defines standard types related to pointer arithmetics */

#ifndef CS_STDDEF_H
#define CS_STDDEF_H


/* === pointer types ============================================================================ */

// just assuming addresses (and ints) are 32-bit
typedef int           intptr_t;
typedef unsigned int  uintptr_t;
typedef int           ssize_t;
typedef unsigned int  size_t;

#define NULL  ((void*)0)


#endif
