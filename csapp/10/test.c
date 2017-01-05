#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char c;
    printf("abcdef\n");
    read(STDIN_FILENO, &c, 1);
    printf("%c\n", c);
    exit(0);
}
