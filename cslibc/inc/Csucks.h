/* Provides aliases for some types and C keywords I don't like.
   The rest of cslibc does not use this, it's here just for convenience. */

#ifndef CSUCKS_H
#define CSUCKS_H


// everybody wants these anyway
#include "stdbool.h"
#include "stddef.h"

#define intern    static  // for use in file scope
#define common    static  // for use in function scope
#define readonly  const   // it's not constant, it's just read-only!

#define byte  char  // to be used with signed/unsigned (that's why it isn't a typedef)


#endif
