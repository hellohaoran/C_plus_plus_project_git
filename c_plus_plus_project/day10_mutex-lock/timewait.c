#include<c43func.h>
int main(){
    struct timeval now,end;
    gettimeofday (&now,NULL);
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond,NULL);
    pthread_mutex_lock(&mutex);
    // pthread_cond_wait(&cond, &mutex);
struct timespec tim;
pthread_cond_timedwait(&cond,&mutex, &tim); 

    pthread_mutex_unlock(&mutex);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    gettimeofday(&end,NULL);
    
    printf("consum %ld s,%ld us \n", now.tv_sec - end.tv_sec , now.tv_usec - end.tv_usec);

}