#include <stdio.h>

int main()
{
    if ((long)((void *)-1) == -1)
        printf("yes\n");
    return 0;
}
