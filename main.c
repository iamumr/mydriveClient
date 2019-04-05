#include "include/func.h"
current_user logined;
int main()
{
    menu();
    int code;
    scanf("%d",&code);
    while(1)
    {
        int tmp=switchMain(code);
        if(11==tmp)
        {
            int socketFd;
            tcpInit(&socketFd,SERVER_IP,SERVER_PORT); 
            train t;
            //发送信号3（空信号），进入线程处理
            t.dataLen=sizeof(char);
            strcpy(t.buf,"3");
            sendCycle(socketFd,(char*)&t,4+t.dataLen);
            int epfd=epoll_create(1);
            struct epoll_event event,evs[2];
            event.events=EPOLLIN;
            event.data.fd=STDIN_FILENO;
            int ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
            ERROR_CHECK(ret,-1,"epoll_ctl");
            event.data.fd=socketFd;
            ret=epoll_ctl(epfd,EPOLL_CTL_ADD,socketFd,&event);
            ERROR_CHECK(ret,-1,"epoll_ctl");
            while(1)
            {
                memset(evs,0,sizeof(evs));
                int readyFdNum=epoll_wait(epfd,evs,2,-1);
                for(int i=0;i<readyFdNum;i++)
                {

                }
            }
        }

    }
    puts(logined.user_login);
    puts(logined.user_token);
}
