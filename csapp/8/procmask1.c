#include "csapp.h"

void handler(int sig)
{
    pid_t pid;
    while ((pid = waitpid(-1, NULL, 0)) > 0)
        deletejob(pid);
    if (errno != ECHILD)
        unix_error("waitpid error");
}

int main(int argc, char **argv)
{
    int pid;
    sigset_t mask;

    Signal(SIGCHLD, handler);
    initjobs();

    while (1) {
        Sigemptyset(&mask);
        Sigaddset(&mask, SIGCHLD);
        Sigprocmask(SIG_BLOCK, &mask, NULL);

        if ((pid = Fork()) == 0) {
            Sigprocmask(SIG_UNBLOCK, &mask, NULL);
            Execve("/bin/date", argv, NULL);
        }
        
        addjob(pid);
        Sigprocmask(SIG_UNBLOCK, &mask, NULL);
    }
    exit(0);
}
