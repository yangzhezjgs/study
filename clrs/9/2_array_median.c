int
2_array_median(int a[], int a_low, int a_high, int b, int b_low, int b_high)
{
    int a_mid, b_mid;

    if (a_low == a_high)
        return (a[a_low] < b[b_low]) ? a[a_low] : b[b_low];

    a_mid = (a_low + a_high) / 2;
    b_mid = (b_low + b_high) / 2;
    if (a[a_mid] == b[b_mid])
        return a[a_mid];
    else if (a[a_mid] < b[b_mid])
        return 2_array_median(a, a_mid + 1, a_high, b, b_low, b_mid - 1);
    else
        return 2_array_median(a, a_low, a_mid - 1, b, b_mid + 1, b_high);
}
