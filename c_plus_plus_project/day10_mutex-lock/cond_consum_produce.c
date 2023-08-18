#include<c43func.h>
// 卖火车票
//2个售票部门, 一个放票部门; 
typedef struct Com_Res_s
{
    int trainTicket;
    int flag;// 用于决定是否要放票;
    pthread_mutex_t mutex; // 保护售票和放票的资源操作
    pthread_cond_t cond;
}Com_Res_t;
void* sellFunc1(void *arg){
sleep(1); // 确保addTicket能够持有锁并wait
Com_Res_t *pShareRes = (Com_Res_t* )arg;
while (1)
{   sleep(1); // 确保addTicket能够持有锁并wait
     pthread_mutex_lock(&pShareRes->mutex); // 锁住
    if(pShareRes->trainTicket>0){
        printf("before sell 1 , tickets = %d\n", pShareRes->trainTicket );
        --pShareRes->trainTicket;
        printf("after sell 1 , tickets = %d\n", pShareRes->trainTicket );
        if(pShareRes->trainTicket == 0 && pShareRes->flag == 0){
            //如果 卖完票之后,没有票了,而且从来没有放过票
            pthread_cond_signal(&pShareRes->cond); // 
            pShareRes->flag = 1; // 将标志位标为 1 ; 

        }else if(pShareRes->trainTicket == 0 && pShareRes->flag == 1){
            pthread_mutex_unlock(&pShareRes->mutex); // 将锁解锁
            break;
        }
    }
    else{
        if(pShareRes->flag == 1){ // 为避免 addticket的线程的pthread_cond_wait的加锁抢不过另一个线程的加锁
       pthread_mutex_unlock(&pShareRes->mutex);
        break;
        }
    }
    pthread_mutex_unlock(&pShareRes->mutex);
}

}
void * sellFunc2(void *arg){
sleep(1); // 确保addTicket能够持有锁并wait
Com_Res_t *pShareRes = (Com_Res_t* )arg;
while (1)
{   sleep(1);
    pthread_mutex_lock(&pShareRes->mutex); // 锁住
    if(pShareRes->trainTicket>0){

        printf("before sell 2 , tickets = %d\n", pShareRes->trainTicket );
        --pShareRes->trainTicket;
        printf("after sell 2 , tickets = %d\n", pShareRes->trainTicket );
        if(pShareRes->trainTicket == 0 && pShareRes->flag == 0){
            pthread_cond_signal(&pShareRes->cond);
            pShareRes->flag = 1; // 将标志位标为 1 ; 

        }else if(pShareRes->trainTicket == 0 && pShareRes->flag == 1){
            pthread_mutex_unlock(&pShareRes->mutex); // 将锁解锁
            break;
        }
     }
     else{ // 其他线程在trainTicket = 0这个时候抢占, 就退出 否则 while 一直循环
          if(pShareRes->flag == 1){// 为避免 addticket的线程的pthread_cond_wait的加锁抢不过另一个线程的加锁
       pthread_mutex_unlock(&pShareRes->mutex);
        break;
        }
    }
    pthread_mutex_unlock(&pShareRes->mutex);
}
pthread_exit(NULL);

}
void *addTicket(void*arg){
Com_Res_t *pShareRes = (Com_Res_t* )arg;
// 执行加票
pthread_mutex_lock(&pShareRes->mutex);
if(pShareRes->flag != 1){
    pthread_cond_wait(&pShareRes->cond, &pShareRes->mutex); // 先睡启用wait阻塞,释放锁; 等到signal到来, 再加锁; 解除阻塞;

}
printf("add ticket!\n");
pShareRes->trainTicket = 10;
pthread_mutex_unlock(&pShareRes->mutex);
pthread_exit(NULL);
  
}
int main(){
    Com_Res_t shareRes;
    shareRes.trainTicket = 10;
    pthread_mutex_init(&shareRes.mutex, NULL);
    pthread_cond_init(&shareRes.cond, NULL);
    pthread_t tid1,tid2,tid3;
    shareRes.flag = 0; // 最开始不需要放票
    pthread_create(&tid1, NULL,sellFunc1,(void*)&shareRes );
    pthread_create(&tid2, NULL,sellFunc2,(void*)&shareRes );
    pthread_create(&tid3, NULL,addTicket,(void*)&shareRes ); // 
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_join(tid3,NULL);

    pthread_mutex_destroy(&shareRes.mutex);
    pthread_cond_destroy(&shareRes.cond);



}