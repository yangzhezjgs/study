#include "csapp.h"

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "%s usage:<0xXXXXXXXX>\n", argv[0]);
        exit(0);
    }

    struct in_addr inaddr;
    unsigned int addr;

    sscanf(argv[1], "%x", &addr);
    inaddr.s_addr = htonl(addr);
    printf("%s\n", inet_ntoa(inaddr));
    exit(0);
}
