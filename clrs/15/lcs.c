#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void
lcs_length(char *x, char *y, int **c)
{
    int m = strlen(x);
    int n = strlen(y);
    int i, j;

    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            if (x[i] == y[j])
                c[i + 1][j + 1] = c[i][j] + 1;
            else if (c[i][j + 1] >= c[i + 1][j])
                c[i + 1][j + 1] = c[i][j + 1];
            else
                c[i + 1][j + 1] = c[i + 1][j];
}

void
print_lcs(int **c, char *x, int i, int j)
{
    if (i == 0 || j == 0)
        return;

    if (c[i][j] == c[i - 1][j])
        print_lcs(c, x, i - 1, j);
    else if (c[i][j] == c[i][j - 1])
        print_lcs(c, x, i, j - 1);
    else {
        print_lcs(c, x, i - 1, j - 1);
        printf("%c", x[i - 1]);
    }
}

int
lcs(char *x, char *y)
{
    int m = strlen(x);
    int n = strlen(y);
    int *c[m + 1];
    int i;

    for (i = 0; i <= m; i++)
        c[i] = calloc(n, sizeof(int));

    lcs_length(x, y, c);
    print_lcs(c, x, m, n);
    printf("\n");

    return c[m][n];
}

int
main(void)
{
    char *x = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
    char *y = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";
    int length = lcs(x, y);

    printf("%d\n", length);
}
