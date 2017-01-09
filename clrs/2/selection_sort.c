void
selection_sort(int array[], int n)
{
    int i, j, smallest;

    for (i = 0; i < n - 1; i++) {
        smallest = i;
        for (j = i; j < n; j++)
            if (array[j] < array[smallest])
                smallest = j;

        int temp = array[i];
        array[i] = array[smallest];
        array[smallest] = temp;
    }
}

