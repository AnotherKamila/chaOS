#include "panic.h"

#pragma GCC diagnostic ignored "-Wunused-parameter" // msg is here to be accessible by the debugger
void kpanic(const char * const msg) {
    // TODO blink led or something
    while (1) ; // so that the CPU state can be examined in the debugger
}
