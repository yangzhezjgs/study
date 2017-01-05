#include <stdlib.h>
#include <string.h>
#include "../exception/assert.h"
#include "../mem/mem.h"
#include "array.h"
#include "arrayrep.h"

void arrayrep_init(array_t array, int length, int size, void *ary)
{
    assert(array);
    assert(ary && length > 0 || length == 0 && ary == NULL);
    assert(size > 0);
    array->length = length;
    array->size = size;
    if (length > 0)
        array->array = ary;
    else
        array->array = NULL;
}

array_t array_new(int length, int size)
{
    array_t array;

    NEW(array);
    if (length > 0)
        arrayrep_init(array, length, size, CALLOC(length, size));
    else
        arrayrep_init(array, length, size, NULL);
    return array;
}

void array_free(array_t *array)
{
    assert(array && *array);
    FREE((*array)->array);
    FREE(*array);
}

void *array_get(array_t array, int i)
{
    assert(array);
    assert(i >= 0 && i < array->length);
    return array->array + i * array->size;
}

void *array_put(array_t array, int i, void *elem)
{
    assert(array);
    assert(i >= 0 && i < array->length);
    assert(elem);
    memcpy(array->array + i * array->size, elem, array->size);
    return elem;
}

int array_length(array_t array)
{
    assert(array);
    return array->length;
}

int array_size(array_t array)
{
    assert(array);
    return array->size;
}

void array_resize(array_t array, int length)
{
    assert(array);
    assert(length >= 0);
    if (array->length = 0)
        array->array = ALLOC(length * array->size);
    else if (length > 0)
        RESIZE(array->array, length * array->size);
    else
        FREE(array->array);
    array->length = length;
}

array_t array_copy(array_t array, int length)
{
    array_t copy;

    assert(array);
    assert(length >= 0);
    copy = array_new(length, arr->size);
    if (copy->length >= array->length && array->length > 0)
        memcpy(copy->array, array->array, array->length * array->size);
    else if (arr->length > copy->length && copy->length > 0)
        memcpy(copy->array, array->array, copy->length * array->size);
    return copy;
}


