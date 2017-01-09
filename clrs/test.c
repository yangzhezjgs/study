#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXNUMBER   1000

int *
get_data(int n)
{
    int *buf, i;

    buf = (int *) malloc(n * sizeof(int));
    if (buf == NULL)
        return NULL;

    srand((unsigned) time(NULL));
    for (i = 0; i < n; i++)
        buf[i] = rand() % MAXNUMBER;

    return buf;
}

void
print_array(int buf[], int n)
{
    int i;

    for (i = 0; i < n; i++)
        printf("%d ", buf[i]);

    printf("\n");
}


int
main(void)
{
    int *buf;

    buf = get_data(100);
    quicksort(buf, 0, 99);
    print_array(buf, 100);

    return 0;
}

