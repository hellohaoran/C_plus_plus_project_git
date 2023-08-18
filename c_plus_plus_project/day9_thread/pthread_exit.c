#include <c43func.h>
void* threadFunc(void * args){
    printf("I am new thread %ld\n",pthread_self() );
    // return (void *)0;
    pthread_exit((void*)2); // 返回值
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
    THREAD_ERROR_CHECK(ret, "pthread_create");
    long retval;
    //主线程要拿&retval所指的内存空间,存储子线程的返回值;
    pthread_join(tid, (void**)&retval);  
    printf("child thread return value = %ld\n", retval); 
    usleep(1);
    //不获取子线程的终止状态,阻塞线程直到tid线程终止;
    // pthread_join(tid, NULL);
    return 0 ; //主綫程終止其他綫程也會終止；
}