#include "csapp.h"

int main(int argc, char **argv, char **envp)
{
    char *col;
    argv[0] = "/bin/ls";

    if (argv[1] == NULL)
        printf("end of NULL\n");

    if((col = getenv("COLUMNS")) != NULL)
        printf("...output is %s columns wide\n", col);

    if (execve(argv[0], argv, envp) < 0)
        unix_error("execve error");
    exit(0);
}
