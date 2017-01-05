#include <stdio.h>
#include <stdlib.h>

#define EXCHANGE(i, j) temp = i; i = j; j = temp;
#define PARENT(i) ((i) / 2)
#define LEFT(i) ((i) * 2)
#define RIGHT(i) ((i) * 2 + 1)

int main()
{
    int a[] = {1, 2};
    int *b = a;

    printf("%d\n", *b++);

    return 0;
}
