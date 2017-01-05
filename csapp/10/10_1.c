#include "csapp.h"

#define DEF_MODE    S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH
#define DEF_UMASK   S_IWGRP|S_IWOTH

int main()
{
    int fd1, fd2;

    umask(DEF_UMASK);
    fd1 = Open("foo.txt", O_WRONLY|O_TRUNC, 0);
    Close(fd1);
//    fd2 = Open("bar.txt", O_WRONLY|O_TRUNC, 0);
    printf("fd2=%d\n", fd2);
    return 0;
}
