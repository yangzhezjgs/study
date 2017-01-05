
int open_clientfd(char *hostname, int port)
{
    int clientfd;
    struct hostent *hp;
    struct sockaddr_in serveraddr;

    if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return -1;
    if ((hp = gethostbyname(hostname)) == NULL)
        return -2;

    bzero((char *)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    bcopy(hp->h_addr_list[0], (char *)&serveraddr.sin_addr.s_addr, hp->h_length);

    if (connect(clientfd, (SA *)&serveraddr, sizeof(serveraddr)) < 0)
        return -1;
    return clientfd;
}





