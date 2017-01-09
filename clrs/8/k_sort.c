void quicksort(int [], int, int);

void
k_sort(int buf[], int n, int k)
{
    int step = n / k;
    int i, j, p;
    int arr[step + 1];

    for (i = 0; i < k; i++) {
        p = 0;
        for (j = i; j < n; j += k)
            arr[p++] = buf[j];
        quicksort(arr, 0, p - 1);
        p = 0;
        for (j = i; j < n; j += k)
            buf[j] = arr[p++];
    }
}

