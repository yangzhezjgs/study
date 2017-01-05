#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

#define MAX_SLEEP 100000
#define CONVERT(val) (((double) val) / (double) RAND_MAX)

pid_t Fork(void)
{
    static struct timeval time;
    unsigned bool, secs;
    pid_t pid;

    gettimeofday(&time, NULL);
    srand(time.tv_usec);

    bool = (unsigned) (CONVERT(rand()) + 0.5);
    secs = (unsigned) (CONVERT(rand()) * MAX_SLEEP);

    if ((pid = fork()) < 0)
        return pid;

    if (pid == 0) {
        if (bool)
            usleep(secs);
    } else {
        if (!bool)
            usleep(secs);
    }

    return pid;
}
