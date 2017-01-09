#include <string.h>
#include <stdio.h>

void
binary_add(int A[], int B[], int C[], int n)
{
    int i, val;

    memset(C, 0, sizeof(int) * (n + 1));

    for (i = 0; i < n; i++) {
        val = A[i] + B[i] + C[i];
        C[i] = val % 2;
        C[i + 1] = val / 2;
    }
}

int
main(void)
{
    int i;
    int A[] = { 1, 0, 1 };
    int B[] = { 1, 1, 0 };
    int C[4];

    binary_add(A, B, C, 3);
    for (i = 0; i < 4; i++)
        printf("%d", C[i]);
    printf("\n");

    return 0;
}



