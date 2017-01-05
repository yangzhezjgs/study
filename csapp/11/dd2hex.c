#include "csapp.h"

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "%s usage: <IP>\n", argv[0]);
        exit(0);
    }
    struct in_addr inaddr;

    if (inet_aton(argv[1], &inaddr) == 0)
        unix_error("aton error");

    printf("0x%x\n", ntohl(inaddr.s_addr));
    exit(0);
}
