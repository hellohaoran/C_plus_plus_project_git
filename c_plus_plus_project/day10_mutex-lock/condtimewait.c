#include<c43func.h>
int main(){
    //
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&cond, NULL); 
    pthread_mutex_lock(&mutex); 
   struct timespec  abstime;
   time_t now ;
   now  = time(NULL);
   puts(ctime(&now));
   abstime.tv_sec = 3+ now;
    abstime.tv_nsec = 0; 
    
    pthread_cond_timedwait(&cond, &mutex,&abstime );
    now = time(NULL);
    puts(ctime(&now)); 
    pthread_mutex_unlock(&mutex); 
}