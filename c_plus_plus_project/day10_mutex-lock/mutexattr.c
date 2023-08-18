#include<c43func.h>
int main(){
    pthread_mutex_t mutex;
    pthread_mutexattr_t mut;
    pthread_mutexattr_init(&mut); // 初始化锁的属性
    // 检错锁对同一把锁加锁, 第二次加锁会报错
    // pthread_mutexattr_settype(&mut,PTHREAD_MUTEX_ERRORCHECK);// 设置锁的属性 
    // 可重入锁,对同一把锁加锁, 重复加锁并不会报错: 
    //原理:对同一把锁重复加锁,就是增加了锁的引用计数,其他线程,只有在锁的引用计数为0时才能加锁;
    //因此加了几次锁就解次锁; 
    pthread_mutexattr_settype(&mut,PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mutex,&mut); // 将锁放到 mutex_init 里面;
    int ret1 = pthread_mutex_lock(&mutex); // 第一次加锁
    THREAD_ERROR_CHECK(ret1, "pthread_mutex_lock "); 
    int ret2 = pthread_mutex_lock(&mutex); // 第一次加锁
    THREAD_ERROR_CHECK(ret2, "pthread_mutex_lock "); 
    pthread_mutex_destroy(&mutex);
    //
 
    //


    //避免活锁,任意个资源执行后,sleep随机时间;
}