#include "csapp.h"

void mmapcopy(int fd, size_t length)
{
    char *bufp;
    
    bufp = Mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0);
    Write(1, bufp, length);
    return;
}

int main(int argc, char **argv)
{
    int fd;
    struct stat stat;

    if (argc != 2) {
        printf("usage: %s <filename>\n", argv[0]);
        exit(0);
    }

    fd = Open(argv[1], O_RDONLY, 0);
    fstat(fd, &stat);
    mmapcopy(fd, stat.st_size);
    exit(0);
}



