int
horner(int x, int buf[], int n)
{
    int i;
    int y = 0;

    for (i = n - 1; i >= 0; i--)
        y = buf[i] + y * x;
}

int 
common(int x, int buf[], int n)
{
    int i;
    int y = buf[0];
    int temp = x;

    for (i = 1; i < n; i++) {
        y += buf[i] * x;
        x *= temp;
    }
}
