#include "csapp.h"

int main()
{
    char *bufp;
    int fd;

    fd = Open("hello.txt", O_RDWR, 0);
    bufp = Mmap(NULL, 1, PROT_WRITE, MAP_SHARED, fd, 0);
    *bufp = 'J';
    exit(0);
}

