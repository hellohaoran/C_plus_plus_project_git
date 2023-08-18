#include <c43func.h>
int global = 10;
void *threadFunc(void *arg)
{
    printf("I am new thread %ld\n", pthread_self());
    //整型指针和void*指针的大小都是一样的;
  
// printf("new thread i = %ld\n",i);
// usleep(0.2);
long* p =(long*)arg; 
*p = *p+1;
printf("new thread i = %ld\n",*p);


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
   long i = 1;
    int ret1 = pthread_create(&tid, NULL, threadFunc,(void*) &i  ); // 参数进行地址传递 被调函数因此可以修改 
    // i = 2;
    // int ret2 = pthread_create(&tid, NULL, threadFunc,(void*) i  ); // 参数是拷贝到另一个线程栈的函数的栈;

    usleep(20);
    printf("main thread i = %ld", i );
    return 0; // 主綫程終止其他綫程也會終止；
}



