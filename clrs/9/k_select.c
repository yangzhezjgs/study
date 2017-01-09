#define SWAP(a, b, t)   \
    do {                \
        t temp = a;     \
        a = b;          \
        b = temp;       \
    } while (0)

int
insertion_sort(int buf[], int n)
{
    int i, j, key;

    for (i = 1; i < n; i++) {
        key = buf[i];
        for (j = i - 1; j >= 0 && buf[j] > key; j--)
            buf[j + 1] = buf[j];
        buf[j + 1] = key;
    }

    return buf[(n - 1) / 2];
}

int
partition(int buf[], int low, int high, int pivot)
{
    int i, j, found;

    found = 0;
    for (i = j = low; i < high; i++)
        if (buf[i] == pivot && found == 0) {
            SWAP(buf[i], buf[high], int);
            found = 1;
            i--;
        } else if (buf[i] <= pivot) {
            SWAP(buf[i], buf[j], int);
            j++;
        }
    SWAP(buf[j], buf[high], int);

    return j;
}


int
k_select(int buf[], int low, int high, int k)
{
    int median[(high - low) / 5 + 1];
    int i, j, pivot, mid;

    if (low == high)
        return buf[low];
    j = 0;
    for (i = low; i < high - 4; i += 5)
        median[j++] = insertion_sort(buf + i, 5);
    if (i != high - 1)
        median[j] = insertion_sort(buf + i, high - i + 1);

    pivot = k_select(median, 0, j, j / 2);
    mid = partition(buf, low, high, pivot) - low + 1;

    if (mid == k)
        return buf[mid + low - 1];
    else if (mid < k)
        return k_select(buf, mid + low, high, k - mid);
    else
        return k_select(buf, low, mid + low - 2, k);
}


