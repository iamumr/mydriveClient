#include "include/func.h"

int tcpInit(int *sfd,char *ip,char *port)
{
    int socketFd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serAddr;
    memset(&serAddr,0,sizeof(serAddr));
    serAddr.sin_family=AF_INET;
    serAddr.sin_port=htons(atoi(port));
    serAddr.sin_addr.s_addr=inet_addr(ip);
    connect(socketFd,(struct sockaddr*)&serAddr,sizeof(serAddr));
    *sfd=socketFd;
    return 0;
}

