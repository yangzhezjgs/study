#include <stdio.h>
#include <stdint.h>

#define SWAP(a, b, t)   \
    do {                \
        t temp = a;     \
        a = b;          \
        b = temp;       \
    } while (0)

#define PARENT(i, d) (((i) - 1) / d)
#define KTH_CHILD(i, k, d) ((i) * (d) + (k))

/* θ(dlgn) */
void
d_max_heapify(int buf[], int size, int i, int d)
{
    int j;
    int largest;

    largest = i;
    for (j = KTH_CHILD(i, 1, d); j < size && j <= KTH_CHILD(i, d, d); j++)
        if (buf[j] > buf[largest])
            largest = j;

    if (largest != i) {
        SWAP(buf[i], buf[largest], int);
        d_max_heapify(buf, size, largest, d);
    }
}

/* θ(dn) */
void
build_d_max_heap(int buf[], int size, int d)
{
    int i;

    for (i = PARENT(size - 1, d); i >= 0; i--)
        d_max_heapify(buf, size, i, d);
}

/* θ(dlgn) */
int
d_extract_max(int buf[], int size, int d)
{
    int max = buf[0];

    buf[0] = buf[size - 1];
    d_max_heapify(buf, size - 1, 0, d);

    return max;
}

/* θ(lgdn) */
void
d_increase_key(int buf[], int size, int i, int key, int d)
{
    if (key < buf[i]) {
        fprintf(stderr, "new key is smaller than current key\n");
        return;
    }

    while (i > 0 && buf[PARENT(i, d)] < key)
        buf[i] = buf[PARENT(i, d)];
    buf[i] = key;
}

/* θ(lgdn) */
void
d_insert(int buf[], int size, int key, int d)
{
    buf[size] = INT32_MIN;
    d_increase_key(buf, size + 1, size, key, d);
}

void
d_heapsort(int buf[], int size, int d)
{
    int i;

    build_d_max_heap(buf, size, d);
    for (i = size - 1; i > 0; i--) {
        SWAP(buf[0], buf[i], int);
        d_max_heapify(buf, i, 0, d);
    }
}


