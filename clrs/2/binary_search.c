int
recursive_binary_search(int buf[], int low, int high, int val)
{
    if (low <= high) {
        int mid = (low + high) / 2;

        if (buf[mid] > val)
            return recursive_binary_search(buf, low, mid - 1, val);
        else if (buf[mid] < val)
            return recursive_binary_search(buf, mid + 1, high, val);
        else
            return mid;
    }

    return -1;
}

int
iterative_binary_search(int buf[], int n, int val)
{
    int low = 0;
    int high = n;
    int mid;

    while (low <= high) {
        mid = (low + high) / 2;
        if (buf[mid] > val)
            high = mid - 1;
        else if (buf[mid] < val)
            low = mid + 1;
        else
            return mid;
    }

    return -1;
}

