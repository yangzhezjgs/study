#include "csapp.h"

int main()
{
    int fd;
    char c;

    if (Fork() == 0) {
        fd = Open("foobar.txt", O_RDONLY, 0);
        Read(fd, &c, 1);
        exit(0);
    }
    Wait(NULL);
    fd = Open("foobar.txt", O_RDONLY, 0);
    Read(fd, &c, 1);
    printf("c=%c\n", c);
    exit(0);
}
