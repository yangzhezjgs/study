int
linear_search(int buf[], int n, int val)
{
    int i;

    for (i = 0; i < n; i++)
        if (buf[i] == val)
            return i;

    return -1;
}
