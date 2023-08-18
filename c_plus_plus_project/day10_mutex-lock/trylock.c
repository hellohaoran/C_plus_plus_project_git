#include<c43func.h>
int main(){
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex,NULL);
    pthread_mutex_trylock(&mutex);
    puts("lock one time!\n");
    int ret = pthread_mutex_trylock(&mutex);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_trylock");
    puts("lock two time!\n");
    pthread_mutex_destroy(&mutex);
    //
    pthread_mutex_t A,B; 
    //
    pthread_mutex_init(&A,NULL);
    pthread_mutex_init(&B,NULL);

    while(1){ // 避免死锁 ; 但是会陷入到活锁; t1对资源A,B顺序要求; t2对资源A,B顺序要求;    
        int ret = pthread_mutex_trylock(&A);
        if(ret!= 0){
            continue;
        }
        ret = pthread_mutex_trylock(&B);
        if(ret != 0){
            pthread_mutex_unlock(&A);
            continue;
        }

    }
    //避免活锁,任意个资源执行后,sleep随机时间;
}