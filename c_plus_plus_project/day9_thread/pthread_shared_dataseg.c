#include <c43func.h>
int global = 10;
void *threadFunc(void *args)
{
    printf("I am new thread %ld\n", pthread_self());
    printf("new thread, global = %d\n", global);
}
int main()
{
    printf("I am main thread %ld\n", pthread_self());
    // 不同的操作系统的pthread_t 类型不同
    //    pthread_t
    // 每个线程启动的时候都要有启动函数作为启动线程的入口; main是主线程的启动函数
    //  *thread 线程id  *attr 线程属性    *start_routine 线程启动函数(子线程的);  *arg 是启动函数的参数
    // void *(*start_routine) (void *) 线程启动函数(子线程的); 把函数参数放在结构体里面把结构体取地址传给参数

    pthread_t tid;
    int ret = pthread_create(&tid, NULL, threadFunc, NULL);
    // sleep(0.5);
    // 证明线程并发执行并且 共享数据段的
    global = 200;
    printf("global = %d\n", global);

    usleep(1);

    return 0; // 主綫程終止其他綫程也會終止；
}



