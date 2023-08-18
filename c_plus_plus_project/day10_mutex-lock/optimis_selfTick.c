#include <c43func.h>

typedef struct shareRes_s
{
    int trainTicket;
    pthread_mutex_t mutex;
} shareRes_t;
void *sellTicket1(void *arg)
{   int cnt =0 ; // 统计卖了多少张票
    shareRes_t *pShareRes = (shareRes_t *)arg;

    while (pShareRes->trainTicket > 0) // 对共享资源的访问要在锁的保护之下 因为在 票数为1, 两个线程都可以进入while;
    {
        pthread_mutex_lock(&pShareRes->mutex); 
        if (pShareRes->trainTicket <=  0)
        {
            //在任何导致锁持有线程退出的场景都要解锁
            pthread_mutex_unlock(&pShareRes->mutex);
            break;
        }
        printf("before 1 sell ticket, num = %d\n", pShareRes->trainTicket);
        --pShareRes->trainTicket;
        cnt++;
        printf("after 1 sell ticket, num = %d\n", pShareRes->trainTicket);
        pthread_mutex_unlock(&pShareRes->mutex);
        // sleep(1);
    }
    printf("sell %d ticket1\n",cnt);
}
void *sellTicket2(void *arg)
{   int cnt = 0; 
    shareRes_t *pShareRes = (shareRes_t *)arg;
    while (pShareRes->trainTicket > 0)
    {
        pthread_mutex_lock(&pShareRes->mutex);
        if(pShareRes->trainTicket <= 0){
           
            pthread_mutex_unlock(&pShareRes->mutex);
             break;
        }
        printf("before 2 sell ticket, num = %d\n", pShareRes->trainTicket);
        --pShareRes->trainTicket;
        cnt++;
        printf("after 2 sell ticket, num = %d\n", pShareRes->trainTicket);
        pthread_mutex_unlock(&pShareRes->mutex);
        // sleep(1);
    }
    printf("sell %d ticket2\n", cnt);
}
int main()
{
    // 锁实现生产者消费者
    pthread_t tid1, tid2;
    shareRes_t shareRes;
    shareRes.trainTicket = 100000;
    // pthread_attr_
    // pthread_mutexattr_init(&)
    pthread_mutex_init(&shareRes.mutex,NULL);
    pthread_create(&tid1, NULL, sellTicket1, (void *)&shareRes);
    pthread_create(&tid2, NULL, sellTicket2, (void *)&shareRes);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_mutex_destroy(&shareRes.mutex);
}