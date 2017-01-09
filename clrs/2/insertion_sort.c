void 
insertion_sort(int array[], int n)
{
    int i, j, key;

    for (i = 1; i < n; i++) {
        key = array[i];

        for (j = i - 1; j >= 0 && array[j] > key; j--)
            array[j + 1] = array[j];

        array[j + 1] = key;
    }
}

void
recursive_insertion_sort(int array[], int n)
{
    int i, key;

    if (n > 1) {
        recursive_insertion_sort(array, n - 1);

        key = array[n - 1];
        for (i = n - 2; i >= 0 && array[i] > key; i--) 
            array[i + 1] = array[i];

        array[i + 1] = key;
    }
}
