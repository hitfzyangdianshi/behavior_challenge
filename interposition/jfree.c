#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdint.h>
#include <dlfcn.h>

#include "jfree.h"


void* myfree(void *pt)
{
    static void* (*real_free)(void*) = NULL;
    if (!real_free)
        real_free = dlsym(RTLD_NEXT, "free");

    void *p = real_free(pt);
   // fprintf(stderr, "free(%p) = %p\n", pt, p);
    return p;
}