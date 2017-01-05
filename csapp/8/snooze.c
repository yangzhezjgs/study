#include "csapp.h"

unsigned int snooze(unsigned int secs)
{
    int rs = sleep(secs);
    printf("Slept for %u of %u secs.\n", secs - rs, secs);
    return rs;
}

void handler(int sig)
{
    return;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s <secs>\n", argv[0]);
        exit(0);
    }

    if (signal(SIGINT, handler) == SIG_ERR)
        unix_error("signal error\n");
    (void) snooze(atoi(argv[1]));
    exit(0);
}


