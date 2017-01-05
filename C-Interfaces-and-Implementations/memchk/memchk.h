#ifndef MEMCHK_H__
#define MEMCHK_H__
#include "../exception/except.h"

extern const except_t mem_failed;

extern void *memchk_alloc(long nbytes, const char *file, int line);
extern void *memchk_calloc(long count, long nbytes, const char *file, int line);
extern void memchk_free(void *ptr, const char *file, int line);
extern void *memchk_resize(void *ptr, long nbytes, const char *file, int line);

#define ALLOC(nbytes) memchk_alloc((nbytes), __FILE__, __LINE__)
#define CALLOC(count, nbytes) memchk_calloc((count), (nbytes), __FILE__, __LINE__)
#define NEW(p) ((p) = ALLOC((long) sizeof(*(p))))
#define NEW0(p) ((p) = CALLOC(1, (long) sizeof(*(p))))
#define FREE(ptr) ((void) (memchk_free((ptr), __FILE__, __LINE__), (ptr) = NULL))
#define RESIZE(ptr, nbytes) ((ptr) = memchk_resize(ptr, nbytes, __FILE__, __LINE__))

#endif
