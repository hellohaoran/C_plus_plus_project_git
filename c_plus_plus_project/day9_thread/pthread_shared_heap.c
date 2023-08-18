#include <c43func.h>
int global = 10;
void *threadFunc(void *arg)
{
    printf("I am new thread %ld\n", pthread_self());
    //整型指针和void*指针的大小都是一样的;
    int *pheap = (int*)arg;
    *pheap = 50;
    printf("new thread *pheap = %d\n",*pheap);
    //操作系统的位数64位(数据总线)决定是8字节的指针类型: 寻址空间
    printf("%ld",sizeof(void*));

}
int main()
{
    printf("I am main thread %ld\n", pthread_self());
    // 不同的操作系统的pthread_t 类型不同
    //    pthread_t
    // 每个线程启动的时候都要有启动函数作为启动线程的入口; main是主线程的启动函数
    //  *thread 线程id  *attr 线程属性    *start_routine 线程启动函数(子线程的);  *arg 是启动函数的参数
    // void *(*start_routine) (void *) 线程启动函数(子线程的); 把函数参数放在结构体里面把结构体取地址传给参数
    int *pheap = (int *)malloc(sizeof(int));
    pthread_t tid;
    *pheap = 100;
    int ret = pthread_create(&tid, NULL, threadFunc, pheap); // 参数是拷贝到另一个线程栈的函数的栈;
    usleep(1);
    printf("main thread *pheap = %d\n",*pheap);
    usleep(1);
    return 0; // 主綫程終止其他綫程也會終止；
}



