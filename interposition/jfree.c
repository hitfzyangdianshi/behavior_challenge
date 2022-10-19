#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <dlfcn.h>

void* free(void *pt)
{
    static void* (*real_free)(void*) = NULL;
    if (!real_free)
        real_free = dlsym(RTLD_NEXT, "free");

    void *p = real_free(pt);
    fprintf(stderr, "free(%p) = %p\n", pt, p);
    return p;
}