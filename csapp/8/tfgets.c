
sigjmp_buf buf;

void handler(int sig)
{
    signal(SIGALRM, SIG_DFL);
    siglongjmp(buf, 1);
}

char *tfgets(char *buf, int bufsize, FILE *stream)
{
    signal(SIGALRM, handler);
    alarm(5);

    int rc = sigsetjmp(buf, 1);
    if (rc == 0)
        return fgets(buf, bufsize, stream);
    else
        return NULL;
}

