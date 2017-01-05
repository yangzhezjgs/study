#include <stdio.h>
#include <string.h>

void copy_int(int val, void *buf, int maxbytes)
{
    if (maxbytes >= sizeof(val))
        memcpy(buf, (void *) &val, sizeof(val));
}

int main(void)
{
    int buf[] = {0, 0, 0, 0};
    int val = 0x1111;
    int i;
    
    printf("bytes: %lu\n", sizeof(val));
    copy_int(val, buf, 2);

    for (i = 0; i < 4; i++)
        printf("%x\t", buf[i]);
    printf("\n");

    return 0;
}




