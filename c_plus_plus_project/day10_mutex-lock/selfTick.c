#include<c43func.h>

typedef struct shareRes_s{
    int trainTicket;
    pthread_mutex_t mutex; 
}shareRes_t;
void *sellTicket1(void * arg){
    shareRes_t *pShareRes = (shareRes_t *)arg;
 
    while (pShareRes->trainTicket >0) // 对共享资源的访问要在锁的保护之下 因为在 票数为1, 两个线程都可以进入while; 
    {   pthread_mutex_lock(&pShareRes->mutex);
    printf("before 1 sell ticket, num = %d\n", pShareRes->trainTicket);
    --(pShareRes->trainTicket);
    printf("after 1 sell ticket, num = %d\n", pShareRes->trainTicket);
      pthread_mutex_unlock(&pShareRes->mutex); 
    sleep(1);      
    }  
   
}
void * sellTicket2(void * arg){
shareRes_t *pShareRes = (shareRes_t *)arg;
while (pShareRes->trainTicket >0)
    {pthread_mutex_lock(&pShareRes->mutex);
    printf("before 2 sell ticket, num = %d\n", pShareRes->trainTicket);
    --(pShareRes->trainTicket);
    printf("after 2 sell ticket, num = %d\n", pShareRes->trainTicket);
    pthread_mutex_unlock(&pShareRes->mutex); 
    sleep(1);      
    }    
}
int main(){
    // 锁实现生产者消费者
    pthread_t tid1,tid2;
    shareRes_t shareRes;
    shareRes.trainTicket = 100;
    pthread_mutex_init(&shareRes.mutex,NULL);
    int ret1 = pthread_create(&tid1,NULL,sellTicket1,(void*) &shareRes);
    THREAD_ERROR_CHECK(ret1,"sellTicket1");
    int ret2 = pthread_create(&tid2,NULL,sellTicket2,(void*)  &shareRes );
    THREAD_ERROR_CHECK(ret2,"sellTicket2");
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_mutex_destroy(&shareRes.mutex); // 将锁销毁
    
}