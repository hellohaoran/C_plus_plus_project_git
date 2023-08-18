#include<c43func.h>
typedef struct Com_res_s{
    int count;
   pthread_mutex_t mutex; 
    pthread_mutex_t mutex2;
   int flag; 
}Com_res_t;
void*thread_1(void * arg){
    Com_res_t * res = (Com_res_t *) arg;   
    while(1){
        pthread_mutex_lock(&res->mutex);
        if((res->count< 10)|| res->flag){ // 
            pthread_mutex_unlock(&res->mutex);
            break;
        }
        printf("before sell num = %d\n",res->count);
        res->count--;
        printf("after sell num = %d\n", res->count);
        pthread_mutex_unlock(&res->mutex);
    }
    pthread_mutex_lock(&res->mutex2);
    res->flag = 1;
    pthread_mutex_unlock(&res->mutex2);
}
void * thread_2(void * arg){
        Com_res_t * res = (Com_res_t *) arg;   
    while(1){
       
    
         if(res->flag== 1){
             pthread_mutex_lock(&res->mutex); 
        if(res->count<=0){ // 
            pthread_mutex_unlock(&res->mutex); // 退回资源
            break;
        }
        printf("thread 2 before sell num = %d\n",res->count);
        res->count--;
        printf("thread 2 after sell num = %d\n", res->count);
        pthread_mutex_unlock(&res->mutex);
        }  
         
    }

}
int main(){
    //实例化资源
    Com_res_t res;
    //设置资源
    res.count = 1000;
    res.flag = 0;
    // 初始化锁
    pthread_mutex_init(&res.mutex, NULL); 
    pthread_mutex_init(&res.mutex2, NULL); 

    pthread_t sid1 ,sid2;
   int ret=  pthread_create(&sid1,NULL,thread_1,(void*)&res);
   THREAD_ERROR_CHECK(ret,"pthread_create");
   int ret2 = pthread_create(&sid2,NULL,thread_2,(void*)&res);
      THREAD_ERROR_CHECK(ret2,"pthread_create");
    pthread_join(sid1, NULL); // 进行线程的join ; 
    pthread_join(sid2, NULL);

}