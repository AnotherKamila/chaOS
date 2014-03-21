#ifndef BINFMT_UTIL_H
#define BINFMT_UTIL_H

#include "device/core.h"

// TODO find out if it is worth it to make these static

static void padzero(word *start, word *end) {
    while (start < end)
        *(start++) = (word)0;
}

static void copy_region(word *ssrc, word *sdest, word *edest) {
    while (sdest < edest)
        *(ssrc++) = *(sdest++);
}

#endif
