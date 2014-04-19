/* a macro to stringify its argument at compile-time */

#ifndef UTIL_STRINGIFY_H
#define UTIL_STRINGIFY_H


#define STRINGIFY(x)  __STRINGIFY2(x) // double macro to ensure all macros get expanded...
#define __STRINGIFY2(x)  #x


#endif
