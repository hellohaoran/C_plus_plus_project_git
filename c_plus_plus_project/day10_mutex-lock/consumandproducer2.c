#include<c43func.h>
//生产者生产 : 在队列不满的情况下;
//消费者消费:在队列不空的情况下
//使用循环队列(数组) ;
#define NUM 10
typedef struct queue_s{
    int elem[NUM]; // 
    int size;  // 元素的大小
    int front; //  头元素 删除
    int rear; // 尾元素后面的元素
}queue_t;
typedef struct ComRes_s{
    queue_t queue;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}ComRes_t;
int cnt= 0;
void* producer(void * arg){
    ComRes_t * pres = (ComRes_t * ) arg;
    while (1)
    {//  只有在 队列不满时才生产 队列满时要等待;
        pthread_mutex_lock(&pres->mutex); 
        if(pres->queue.size == NUM){
            pthread_cond_wait(&pres->cond, &pres->mutex); // 在队列满时解锁进行等待 
        }
        pres->queue.elem[pres->queue.rear] = cnt++;
        pres->queue.rear = (pres->queue.rear +1) %NUM;
        pres->queue.size ++ ;
        printf("producer front = %d , rear = %d\n", pres->queue.elem[pres->queue.front], pres->queue.elem[(pres->queue.rear -1 + NUM) % NUM]); // 生产者的判断
        if(pres->queue.size == 1){
            // 如果队列的元素为1 则 唤醒 消费者
            pthread_cond_signal(&pres->cond); 
        }
        pthread_mutex_unlock(&pres->mutex);

    usleep(500000);
    }
    
}
void * consumer(void * arg){
        ComRes_t * pres = (ComRes_t * ) arg;
    while (1)
    {//  只有在 队列不满时才生产 队列满时要等待;
        pthread_mutex_lock(&pres->mutex); 
        if(pres->queue.size == 0){
            pthread_cond_wait(&pres->cond, &pres->mutex); // 在队列满时解锁进行等待 
        }
        // pres->queue.elem[pres->queue.rear] = cnt++;
        pres->queue.front = (pres->queue.front +1) %NUM;
        pres->queue.size --  ;
        printf("consumer front = %d , rear = %d\n", pres->queue.elem[pres->queue.front], pres->queue.elem[(pres->queue.rear -1 + NUM) % NUM]); // 生产者的判断
        if(pres->queue.size == 9){
            // 如果队列的元素为9 队列不满 则 唤醒 生产者
            pthread_cond_signal(&pres->cond); 
        }
        pthread_mutex_unlock(&pres->mutex);

    sleep(1);
    }
    
}
int main(){
   ComRes_t res;
   bzero(&res.queue,sizeof(res.queue) ); 
   pthread_mutex_init(&res.mutex, NULL);
   pthread_cond_init(&res.cond, NULL);
   pthread_t tid1 , tid2;
   pthread_create(&tid1,NULL,producer,(void*)&res);
   pthread_create(&tid2,NULL,consumer,(void*)&res);
   pthread_join(tid1, NULL);
   pthread_join(tid2, NULL);
  pthread_mutex_destroy(&res.mutex);
    pthread_cond_destroy(&res.cond); 
}