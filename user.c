#include "include/func.h"

int userReg()
{
    char user_login[255];
    unsigned char user_pass[128];
    char user_email[255];
    char display_name[255];
    printf("请输入用户名:\n");
    scanf("%s",user_login);
    printf("请输入用户密码:\n");
    scanf("%s",user_pass);
    printf("请输入邮箱：\n");
    scanf("%s",user_email);
    printf("请输入昵称：\n");
    scanf("%s",display_name);
    int socketFd;
    tcpInit(&socketFd,SERVER_IP,SERVER_PORT);
    char code[4]="0"; 
    train t;
    t.dataLen=strlen(code);
    strcpy(t.buf,code);
    //发送操作码
    sendCycle(socketFd,(char*)&t,t.dataLen+4);
    t.dataLen=strlen(user_login);
    strcpy(t.buf,user_login);
    //发送用户名
    sendCycle(socketFd,(char*)&t,4+t.dataLen);
    //接收slat值
    recvCycle(socketFd,(char*)&t.dataLen,sizeof(int));
    recvCycle(socketFd,t.buf,t.dataLen);
    puts(t.buf); 
    //加密密码并发送密文
    passedSHA512(user_pass,strlen((char*)user_pass),t.buf); 
    puts((char*)user_pass); 
    t.dataLen=strlen((char*)user_pass);
    memset(t.buf,0,sizeof(t.buf));
    strcpy(t.buf,(char*)user_pass);
    sendCycle(socketFd,(char*)&t,4+t.dataLen);
    //发送邮箱
    t.dataLen=strlen(user_email);
    memset(t.buf,0,sizeof(t.buf));
    strcpy(t.buf,user_email);
    sendCycle(socketFd,(char*)&t,4+t.dataLen); 
    //发送昵称
    t.dataLen=strlen(display_name);
    memset(t.buf,0,sizeof(t.buf));
    strcpy(t.buf,display_name);
    sendCycle(socketFd,(char*)&t,4+t.dataLen);
    //接收返回信号
    recvCycle(socketFd,(char*)&t.dataLen,sizeof(int));
    recvCycle(socketFd,(char*)&t.buf,t.dataLen);
    if(strcmp(t.buf,"0")==0)
    {
        printf("用户创建成功\n");
    }else{
        printf("用户创建失败\n");
    }
    
    //puts(user_pass);
    //puts(t.buf); 
    
}
int userLogin()
{
    extern current_user logined; 
    unsigned char user_pass[128];
    char display_name[255];
    printf("请输入用户名:\n");
    scanf("%s",logined.user_login);
    printf("请输入用户密码:\n");
    scanf("%s",user_pass);
    int socketFd;
    tcpInit(&socketFd,SERVER_IP,SERVER_PORT);
    char code[4]="1"; 
    train t;
    t.dataLen=strlen(code);
    strcpy(t.buf,code);
    //发送操作码
    sendCycle(socketFd,(char*)&t,t.dataLen+4);
    t.dataLen=strlen(logined.user_login);
    strcpy(t.buf,logined.user_login);
    //发送用户名
    sendCycle(socketFd,(char*)&t,4+t.dataLen);
    //接收slat值
    recvCycle(socketFd,(char*)&t.dataLen,sizeof(int));
    memset(t.buf,0,sizeof(t.buf)); 
    recvCycle(socketFd,t.buf,t.dataLen);
    //puts(t.buf); 
    //加密密码并发送密文
    passedSHA512(user_pass,strlen((char*)user_pass),t.buf); 
    //puts((char*)user_pass);
    strcpy(logined.passwd,(char*)user_pass);//保存至全局变量
    t.dataLen=strlen((char*)user_pass);
    memset(t.buf,0,sizeof(t.buf));
    strcpy(t.buf,(char*)user_pass);
    sendCycle(socketFd,(char*)&t,4+t.dataLen);
    //接收token 
    recvCycle(socketFd,(char*)&t.dataLen,sizeof(int));
    if(t.dataLen==0){
        printf("用户名或密码错误，登录失败！\n");
        close(socketFd); 
        return -1;
    } 
    memset(t.buf,0,sizeof(t.buf));
    recvCycle(socketFd,(char*)&t.buf,t.dataLen);
    strcpy(logined.user_token,t.buf);
    //puts(t.buf);
    //接收返回信号
    recvCycle(socketFd,(char*)&t.dataLen,sizeof(int));
    memset(t.buf,0,sizeof(t.buf)); 
    recvCycle(socketFd,(char*)&t.buf,t.dataLen);
    if(strcmp(t.buf,"0")==0)
    {
        printf("用户登录成功\n");
        strcpy(logined.dir,"/");
        logined.dir_code=0;
    }else{
        printf("用户登录失败\n");
        memset(&logined,0,sizeof(current_user));
    }
    close(socketFd);
}
