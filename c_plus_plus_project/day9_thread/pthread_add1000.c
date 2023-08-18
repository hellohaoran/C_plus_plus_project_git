#include <c43func.h>
#define NUM 1000000
void* threadFunc(void * arg){
    printf("I am new thread %ld\n",pthread_self() );
    long *pnum = (long *)arg;
    for(int i =0;i<NUM;++i){
        ++(*pnum);
    }
pthread_exit(NULL);
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
    long num=0;

    int ret = pthread_create(&tid, NULL, threadFunc, (void*) &num); // 段错误一般是指针问题
    for(int i =0;i<NUM;++i){
        ++num;
    }
    long retval;
    pthread_join(tid,(void**)&retval);
    printf("retval = %ld\n",retval);
    sleep(1);
    printf("num = %ld\n",num);
    return 0 ; //主綫程終止其他綫程也會終止；
}