#include<c43func.h> 
void* threadFunc(void * arg){
    time_t now = time(NULL);
    char buf[4096] = {0};
    // char * p = ctime(&now); // p是在数据段上面的  
    char * p = ctime_r(&now,buf);
    printf("%s",p);
    sleep(5);
    // p = ctime(&now); // p是在数据段上面的
    printf("%s",p);
}
int main(){
    // 下面代码介绍了线程不安全的例子; ctime分配的内存空间是在数据段里; 
    pthread_t tid;
    pthread_create( &tid, NULL,threadFunc, NULL);
     sleep(3);
    time_t  now = time(NULL);
    char buf[4096] = {0};
    // char * p = ctime(&now); // p是在数据段上面的  
    char*p = ctime_r(&now,buf);
    printf("main thread %s\n", p);
    pthread_join(tid, NULL);
}