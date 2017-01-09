#define SWAP(a, b ,t)   \
    do {                \
        t temp = a;     \
        a = b;          \
        b = temp;       \
    } while (0)

#define PARENT(i) (((i) - 1) / 2) 
#define LEFT(i) ((i) * 2 + 1)
#define RIGHT(i) ((i) * 2 + 2)

/* θ(lgn) */
void
max_heapify(int buf[], int size, int i)
{
    int largest, left, right;

    largest = i;
    left = LEFT(i);
    right = RIGHT(i);

    if (left <= size - 1 && buf[left] > buf[largest])
        largest = left;
    if (right <= size - 1 && buf[right] > buf[largest])
        largest = right;

    if (largest != i) {
        SWAP(buf[i], buf[largest], int);
        max_heapify(buf, size, largest);
    }
}

/* θ(nlgn) */
void
build_max_heap(int buf[], int size)
{
    int i;

    for (i = PARENT(size - 1); i >= 0; i--)
        max_heapify(buf, size, i);
}


/* θ(nlgn) */
void
heapsort(int buf[], int size)
{
    int i;
    build_max_heap(buf, size);

    for (i = size - 1; i > 0; i--) {
        SWAP(buf[0], buf[i], int);
        size--;
        max_heapify(buf, size, 0);
    }
}
