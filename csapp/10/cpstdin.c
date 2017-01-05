#include "csapp.h"

int main(void)
{
    char c;
    int size;
    while (Read(STDIN_FILENO, &c, 1) != 0) {
        printf("*");
        fflush(stdout);
        Write(STDOUT_FILENO, &c, 1);
    }
    exit(0);
}
