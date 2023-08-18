#include <c43func.h>
void clean1(void * arg){
    printf("I am clean1\n");
    free(arg);
}
void clean2(void * arg){
    printf("I am clean2\n");
    free(arg);
}
void* threadFunc(void * args){
    printf("I am new thread %ld\n",pthread_self() );
    int *p1 =(int*) malloc(4);//申请资源后,马上将对应的清理行为压栈
    //cleanup_push和cleanup_pop中间一定要没有取消点函数; 
    pthread_cleanup_push(clean1,p1);
    int*p2 = (int*)malloc(2);
    
    pthread_cleanup_push(clean2,p2);
    // pthread_exit(NULL);
    //取消点是pthread_cleanup_pop 
    //pthread_cleanup_pop 参数为正数时会主动调用清理函数; 为0不会主动调用;
    pthread_cleanup_pop(1); // 先弹clean2
    pthread_cleanup_pop(1);// 再弹clean2


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

    
    usleep(20);
    
    return 0 ; //主綫程終止其他綫程也會終止；
}