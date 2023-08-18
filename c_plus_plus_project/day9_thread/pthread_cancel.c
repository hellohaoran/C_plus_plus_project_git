#include <c43func.h>
void* threadFunc(void * args){
    while (1)
    {

    };
    
    printf("I am new thread %ld\n",pthread_self() );
    // pthread_exit((void *) 0);
}
int main()
{
    printf("I am main thread %ld\n",pthread_self() );
    // 不同的操作系统的pthread_t 类型不同
    //    pthread_t
    // 每个线程启动的时候都要有启动函数作为启动线程的入口; main是主线程的启动函数
    //  *thread 线程id  *attr 线程属性    *start_routine 线程启动函数(子线程的);  *arg 是启动函数的参数
    // void *(*start_routine) (void *) 线程启动函数(子线程的); 把函数参数放在结构体里面把结构体取地址传给参数
 


       pthread_t tid ;
    int ret = pthread_create(&tid, NULL, threadFunc, NULL); 
    //给tid线程发送终止请求; ==>相当于进程的kill信号; 

    // 会立刻修改目标线程的取消标志位;到目标线程运行到一些取消点(特殊函数)
    pthread_cancel(tid);
    void* retval;
    pthread_join(tid, &retval);
    printf("child thread dreturn value = %ld\n",(long)retval);
    
    usleep(1);
    
    return 0 ; //主綫程終止其他綫程也會終止；
}