#include<c43func.h>
enum{
    FREE,
    BUSY
};
//枚举类型相当于多个宏
typedef struct workerData_s{
    pid_t pid ; // 进程id
    int status;// 进程状态:FREE或者 BUSY
    int pipfd ; // 进程的管道描述符
}workerData_t;
int makeChild(workerData_t * workerArr,int workerNum  );
int eventHandler(int pipFd) ;