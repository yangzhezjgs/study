#include <unistd.h>
#include <stdio.h>

int main()
{
    char *filename = "./hello";
    char *argv[] = { "./hello", NULL };

    printf("1\n");
    execve(filename, argv, NULL);
    printf("2\n");
    return 0;
}
