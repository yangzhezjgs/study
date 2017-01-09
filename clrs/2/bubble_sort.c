void
bubble_sort(int buf[], int n)
{
    int i, j;

    for (i = 0; i < n - 1; i++)
        for (j = n - 1; j > i; j--)
            if (buf[j] < buf[j - 1]) {
                int temp = buf[j];
                buf[j] = buf[j - 1];
                buf[j - 1] = temp;
            }
}

