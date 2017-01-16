#define _GNU_SOURCE
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8000);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    int on = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on));

    bind(fd, (struct sockaddr *) &addr, sizeof(addr));
    listen(fd, 5);

    int epfd = epoll_create(1024);
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = fd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event);


    for (;;) {
        struct epoll_event e;
        if (epoll_wait(epfd, &e, 1, -1) == -1)
            perror("epoll_wait");
        if (e.data.fd == fd) {
            printf("accept\n");
            int connfd = accept4(fd, NULL, NULL, SOCK_NONBLOCK);
            struct epoll_event event;
            event.events = EPOLLIN | EPOLLOUT | EPOLLET;
            event.data.fd = connfd;
            epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &event);
        } else {
        if (e.events & EPOLLIN)
            printf("ready to read\n");
        if (e.events & EPOLLOUT)
            printf("ready to write\n");
        }
    }
}

