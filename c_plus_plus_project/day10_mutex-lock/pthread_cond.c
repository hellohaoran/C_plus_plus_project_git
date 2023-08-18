#include<c43func.h>
// 条件变量的等待要配合锁一起使用 : 先加锁后使用wait条件变量
typedef struct shareRes_s{
    int flag;
    pthread_cond_t cond;
    pthread_mutex_t mutex;

}shareRes_t;
void * threadFunc(void * arg){
    // sha
    shareRes_t*  pres = (shareRes_t*)arg;
    // 先加锁 为了保护使得pthread_cond_wait 的flag 
    pthread_mutex_lock(&pres->mutex); 
    //只有在加锁的状态下,才能使用wait
    // 希望检查状态与陷入等待是一个原子操作
    if(pres->flag == 0){   // 必须要有条件等待状态
    pthread_cond_wait(&pres->cond, &pres->mutex);  // 先睡并将锁解开,直到收到signal 被唤醒;先加锁;  
    }
    // 从wait中唤醒, 说明前面的事件已经完成;
    puts("world  ");
    pthread_mutex_unlock(&pres->mutex);
    pthread_exit(NULL);
}
int main(){
    shareRes_t  res;
    pthread_mutexattr_t mutexattr;
    pthread_mutexattr_init(&mutexattr); 
    res.flag = 0; 
    pthread_mutexattr_settype(&mutexattr,PTHREAD_MUTEX_NORMAL);// 普通锁
    pthread_mutex_init(&res.mutex, &mutexattr); // 初始化锁
    pthread_cond_init(&res.cond , NULL);
    pthread_t tid;
    pthread_create(&tid, NULL, threadFunc,(void*)&res); 
    sleep(1);
    pthread_mutex_lock(&res.mutex);

    puts("hello!");
    // pthread_mutex_lock(&res.mutex);
    res.flag =1 ;
    // pthread_mutex_unlock(&res.mutex);
    pthread_cond_signal(& res.cond  );
    sleep(1);
    pthread_mutex_unlock(&res.mutex);
 
    pthread_join(tid,NULL);
    

}