#define SWAP(a, b, t)   \
    do {                \
        t temp = a;     \
        a = b;          \
        b = temp;       \
    } while (0)         \

int
partition(int buf[], int low, int high)
{
    int i, j, pivot;

    pivot = buf[high];
    i = low;
    for (j = low; j < high; j++)
        if (buf[j] <= pivot) {
            SWAP(buf[i], buf[j], int);
            i++;
        }
    SWAP(buf[i], buf[high], int);

    return i;
}

void
tail_recursive_quicksort(int buf[], int low, int high)
{
    int mid;

    while (low < high) {
        mid = partition(buf, low, high);
        tail_recursive_quicksort(buf, low, mid - 1);
        low = mid + 1;
    }
}

void
better_tail_recursive_quicksort(int buf[], int low, int high)
{
    int mid;

    while (low < high) {
        mid = partition(buf, low, high);
        /* 大的用尾递归 */
        if (mid < (low + high) / 2) {
            better_tail_recursive_quicksort(buf, low, mid - 1);
            low = mid + 1;
        } else {
            better_tail_recursive_quicksort(buf, mid + 1, high);
            high = mid - 1;
        }
    }
}
