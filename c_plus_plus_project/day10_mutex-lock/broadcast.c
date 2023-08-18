// 当线程执行 pthread_cond_wait 时会解锁 并把自己这个线程加入到唤醒队列里面; 通常的signal 只会唤醒唤醒队列的首元素 ;
// 但broadcast 会唤醒唤醒队列的所有元素
#include<c43func.h>
// 条件变量的等待要配合锁一起使用 : 先加锁后使用wait条件变量
typedef struct shareRes_s{
    int cnt;
    pthread_cond_t cond;
    pthread_mutex_t mutex;

}shareRes_t;
void * threadFunc(void * arg){
    shareRes_t*  pres = (shareRes_t*)arg;
    // 先加锁 为了保护使得pthread_cond_wait 的flag 
    pthread_mutex_lock(&pres->mutex); 
    //只有在加锁的状态下,才能使用wait
    // 希望检查状态与陷入等待是一个原子操作
    // if(pres->cnt == 0){   // 必须要有条件等待状态
    //while 可以避免os虚假唤醒;  每次醒来时检查是否满足条件; 
    while(pres->cnt == 0){ // 如果是 if 别人可能在if里面添加条件  
    pthread_cond_wait(&pres->cond, &pres->mutex); // 先睡并将锁解开,直到收到signal 被唤醒;先加锁;  
 
    }
    printf("cnt  = %d \n", pres->cnt);
    pres->cnt --;
    printf("cnt  = %d \n", pres->cnt);
  

    // 从wait中唤醒, 说明前面的事件已经完成;
    puts("world  ");
    pthread_mutex_unlock(&pres->mutex);
    pthread_exit(NULL);
}
int main(){
    shareRes_t  res;
    pthread_mutexattr_t mutexattr;
    pthread_mutexattr_init(&mutexattr); 
    res.cnt = 0; 
    pthread_mutexattr_settype(&mutexattr,PTHREAD_MUTEX_NORMAL);// 普通锁
    pthread_mutex_init(&res.mutex, &mutexattr); // 初始化锁
    pthread_cond_init(&res.cond , NULL); // 
    pthread_t tid1 , tid2;
    // 创建以tid1为线程名的线程; 并将 res 作为共享资源传递到线程;
    pthread_create(&tid1, NULL, threadFunc,(void*)&res); 
    pthread_create(&tid2, NULL, threadFunc,(void*)&res); 
    sleep(1);
    pthread_mutex_lock(&res.mutex); 

    puts("hello!");

    res.cnt =1 ;
  
    // pthread_cond_signal(& res.cond  );
     pthread_cond_broadcast(& res.cond  );

    sleep(1);
    pthread_mutex_unlock(&res.mutex);
 
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);

 

}
