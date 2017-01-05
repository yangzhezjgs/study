#include <stdlib.h>
#include <stddef.h>
#include "../exception/assert.h"
#include "../exception/except.h"
#include "mem.h"

const except_t mem_failed = {"Allocation Failed"};

static void raise_mem_failed(const char *file, int line)
{
    if (file == NULL)
        RAISE(mem_failed);
    else
        except_raise(&mem_failed, file, line);
}

void *mem_alloc(long nbytes, const char *file, int line)
{
    void *ptr;

    assert(nbytes > 0);
    ptr = malloc(nbytes);
    if (ptr == NULL)
        raise_mem_failed(file, line);
    return ptr;
}

void *mem_calloc(long count, long nbytes, const char *file, int line)
{
    void *ptr;

    assert(count > 0);
    assert(nbytes > 0);
    ptr = calloc(count, nbytes);
    if (ptr == NULL)
        raise_mem_failed(file, line);
    return ptr;
}

void mem_free(void *ptr, const char *file, int line)
{
    if (ptr)
        free(ptr);
}

void *mem_resize(void *ptr, long nbytes, const char *file, int line)
{
    assert(ptr);
    assert(nbytes > 0);
    ptr = realloc(ptr, nbytes);
    if (ptr == NULL)
        raise_mem_failed(file, line);
    return ptr;
}
