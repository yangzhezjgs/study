#ifndef ARRAY_H__
#define ARRAY_H__

typedef struct array_t *array_t;

extern array_t array_new(int length, int size);
extern void array_free(array_t *arr);
extern int array_length(array_t arr);
extern int array_size(array_t arr);
extern void *array_get(array_t arr, int i);
extern void *array_put(array_t arr, int i, void *elem);
extern void array_resize(array_t arr, int length);
extern array_t array_copy(array_t arr, int length);

#endif
