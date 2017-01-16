#!/usr/bin/env python
# encoding: utf-8

from socket import *
from select import *

listen_fd = socket()
listen_fd.bind(('localhost', 8000))
listen_fd.setblocking(False)
listen_fd.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
listen_fd.listen(5)

epfd = epoll()
epfd.register(listen_fd, EPOLLIN)
while True:
    events = epfd.poll()
    for fd, event in events:
        if fd == listen_fd.fileno():
            connfd, _ = listen_fd.accept()
            epfd.register(connfd, EPOLLET | EPOLLIN | EPOLLOUT)
        else:
            if event & EPOLLIN:
                print("ready to read")
            if event & EPOLLOUT:
                print("ready to write")
