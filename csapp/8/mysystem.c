#include "csapp.h"

int mysystem(char *command)
{
    pid_t pid;
    int *status;

    char *argv[4] = { "/bin/sh", "-c", command, NULL };

    if ((pid = Fork()) == 0) {
        if (execve(argv[0], argv, environ) < 0) {
            return 127;
        }
    } else {
        if (waitpid(-1, &status, 0) < 0) {
            return -1;
        } else {
            if (WIFEXITED(status))
                return WEXITSTATUS(status);
            else
                return status;
        }
    }
}

        
            

