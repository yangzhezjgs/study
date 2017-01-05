#ifndef ARRAYREP_H__
#define ARRAYREP_H__

struct array_t {
    int length;
    int size;
    char *array;
};

extern void arrayrep_init(struct array_t *array, int length, int size, void *ary);

#endif
