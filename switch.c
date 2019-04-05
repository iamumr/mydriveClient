#include "include/func.h"
//功能模块切换逻辑

int switchMain(int code)
{
    switch(code){
    case 1:
        userReg();
        break;
    case 2:
        userLogin();
        break;
    case 3:
        return -1;
    }
    return 0;
}

