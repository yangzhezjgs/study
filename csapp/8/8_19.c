#include "csapp.h"

void foo(int n)
{
    int i;

    for (i = 0; i < n; i++)
        Fork();
    printf("hello\n");
    exit(0);
}

int main()
{
    foo(4);
    exit(0);
}
