#define _GNU_SOURCE
#include <sys/mman.h>
#include <errno.h>
#include <sys/epoll.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sched.h>
#include <signal.h>
#include <sys/msg.h>
#include <strings.h>
#include <syslog.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <openssl/sha.h>
#include <openssl/md5.h>
#define args_check(argc,num) {if(argc!=num) {printf("error args\n");return -1;}}
#define ERROR_CHECK(ret,retval,funcname) {if(ret==retval) {perror(funcname);return -1;}}
#define THREAD_ERROR_CHECK(ret,funcname) {if(ret != 0) {printf("%s failed %s\n",funcname,strerror(ret));return -1;}}

typedef struct{
	pid_t pid;
	int fd;
	short busy;//代表子进程是否忙碌,0代表不忙碌，1代表忙碌
}Process_Data;
//小火车
typedef struct{
	int dataLen;
	char buf[1000];
}train;
int tcpInit(int*,char*,char*);
int sendFd(int,int);
int recvFd(int,int*);
//int tranFile(int);
int sendCycle(int,char*,int);
int recvCycle(int,char*,int);
#define FILENAME "file"
#define SERVER_IP "192.168.5.208"
#define SERVER_PORT "8888"
#define SALT_STR_LEN 10
int menu();
int userReg();
int switchMain(int code);
int userLogin();
int passedSHA512(unsigned char *passwd,int len,char *salt);//密码加密
typedef struct{
    char user_login[255];
    char passwd[128];
    char user_token[32];
    char display_name[255];//昵称
    char dir[2000];//当前所在目录
    int dir_code;//目录编号
}current_user;
