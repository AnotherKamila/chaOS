/* definitions common for all binary formats (types etc.) */

#ifndef BINFMT_COMMON_H
#define BINFMT_COMMON_H


#include "core.h"

// TODO should contain a file pointer or something, not a memory address one day
typedef struct {
    void *img;
} program_img;

typedef struct {
    void *start, *end;
    void *entry;
} exec_img;


#endif
