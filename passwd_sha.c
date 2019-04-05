#include "include/func.h"

int passedSHA512(unsigned char *passwd,int len,char *salt)
{
    SHA512_CTX stx; 
    SHA512_Init(&stx);
    SHA512_Update(&stx,passwd,len);
    SHA512_Update(&stx,salt,SALT_STR_LEN);
    unsigned char sha[64]; 
    SHA512_Final(sha,&stx);
    //printf("%hhn\n",sha);
    //for(int i=0;i<64;i++)
    //{
    //    printf("%02x",sha[i]);
    //}
    unsigned char passwdSHA[128]={0};
    int lens=0;
    for(int i=0;i<64;i++)
    {
        lens+=sprintf(passwdSHA+lens,"%x",sha[i]);
    }
    memcpy(passwd,passwdSHA,128);
    //printf("\n");
}

