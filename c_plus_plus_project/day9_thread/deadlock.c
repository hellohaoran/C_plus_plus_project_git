#include<c43func.h>
int main(){
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex,NULL);
    pthread_mutex_lock(&mutex);
    puts("lock one time!\n");
    pthread_mutex_lock(&mutex);
    puts("lock two time!\n");
    pthread_mutex_destroy(&mutex);
}