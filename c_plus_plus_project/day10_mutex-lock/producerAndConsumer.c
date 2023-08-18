#include<c43func.h>
#define NUM 10
//用数组实现循环队列
// 最初有0个商品
// 每1s 生产一个
// 每0.5s 消费一个
// 消费者在队列为零时陷入等待
//生产者在队列为满时陷入等待 
typedef struct queue_s{
    int elem[NUM];
    int size;
    int front; // 表示队首的下标(队首出队)
    int rear;  // 是要插入队列的元素 ; 队尾是rear - 1;
}queue_t;
typedef struct ShareRes_s{
    queue_t queue;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}ShareRes_t;
int cnt = 0; // 
void *producer(void* arg){
ShareRes_t * pShareRes = (ShareRes_t * )arg;
while(1){
    //生产者;
    pthread_mutex_lock(&pShareRes->mutex); // 加锁
    if(pShareRes->queue.size == NUM){ 
        // 将锁解开; 并进入wait状态; 之后等待signal的到达, 将锁加上;
        pthread_cond_wait(&pShareRes->cond, &pShareRes->mutex); // 将锁揭开; 并进入wait状态; 直到有signal传入;  再把锁锁上; 
    }
    // 行为生产商品
    //循环队列

    pShareRes->queue.elem[pShareRes->queue.rear] = cnt++; // rear指向队尾元素的下个元素将元素入队;
    pShareRes->queue.rear = (pShareRes->queue.rear + 1) %NUM; 
    ++pShareRes->queue.size; // 
    printf("producer size = %d , front = %d , rear = %d\n",
            pShareRes->queue.size,
            pShareRes->queue.elem[pShareRes->queue.front],
            pShareRes->queue.elem[(pShareRes->queue.rear-1 + NUM) % NUM]);
    if(pShareRes->queue.size == 1){ // 有了商品唤醒消费者
    pthread_cond_signal(&pShareRes->cond);
    }
    pthread_mutex_unlock(&pShareRes->mutex);
        usleep(500000);         
}

}
void* consumer(void * arg){
ShareRes_t * pShareRes = (ShareRes_t * )arg;
while(1){
    //消费者;
    pthread_mutex_lock(&pShareRes->mutex); // 加锁
    if(pShareRes->queue.size == 0){ // 队列为0 等待
        // 将锁解开; 并进入wait状态; 之后等待signal的到达, 将锁加上;
        pthread_cond_wait(&pShareRes->cond, &pShareRes->mutex); 
    }
    // 行为生产商品
    //循环队列

    // pShareRes->queue.elem[pShareRes->queue.rear-1] = cnt++;
    pShareRes->queue.front = (pShareRes->queue.front + 1) %NUM; // front出队列;  这样 循环队列 
    --pShareRes->queue.size;
    printf("consumer size = %d , front = %d , rear = %d\n",
            pShareRes->queue.size,
            pShareRes->queue.elem[pShareRes->queue.front],
            pShareRes->queue.elem[(pShareRes->queue.rear-1 + NUM) % NUM]); // 0-1 = -1 则 +NUM
    if(pShareRes->queue.size == 9){ // 队列不满通知生产者;生产
    pthread_cond_signal(&pShareRes->cond);
    }
    pthread_mutex_unlock(&pShareRes->mutex);
    sleep(1);
}
}
int main(){
   
 ShareRes_t res;
    pthread_mutex_init(&res.mutex,NULL);
    bzero(&res.queue,sizeof(res.queue));
    pthread_cond_init(&res.cond, NULL);
    pthread_t tid1;
    pthread_t tid2;
    int ret1 = pthread_create(&tid1,NULL,producer,(void*)&res);
    THREAD_ERROR_CHECK(ret1,"producer");
    int ret2 = pthread_create(&tid2,NULL,consumer,(void*)&res);
    THREAD_ERROR_CHECK(ret1,"consumer");

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_mutex_destroy(&res.mutex);
    pthread_cond_destroy(&res.cond); 



}
