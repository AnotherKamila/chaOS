/* a collection of preprocessor magic */
/* warning: reading this file may cause permanent brain injury, open a portal to hell under your bed
   or otherwise damage your health */

#ifndef UTIL_MACROS_H
#define UTIL_MACROS_H


// a macro to stringify its argument at compile-time
#define STRINGIFY(x)  __STRINGIFY2(x) // double macro to ensure all macros get expanded...
#define __STRINGIFY2(x)  #x


#endif
