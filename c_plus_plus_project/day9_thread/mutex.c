#include <c43func.h>
// 1.封装线程共享资源
#define NUM 1000000
typedef struct shareRes_s
{
    pthread_mutex_t mutex;
    int count; // 将这个数加到1000万
} shareRes_t;
void *threadFunc(void *arg)
{
    shareRes_t *pShareRes = (shareRes_t *)(arg);
    for (int i = 0; i < NUM; i++)
    {
        pthread_mutex_lock(&(pShareRes->mutex));   // 加锁
        (*pShareRes).count++;                      // 线程共享资源的访问都要放到临界区
        pthread_mutex_unlock(&(pShareRes->mutex)); // 解锁
    }
}

int main()
{
    // pthread_mutex
    //  pthread_mutex_t mutex;
    shareRes_t shareRes;
    shareRes.count = 0;
    printf("num = %d", shareRes.count);
    pthread_mutex_init(&shareRes.mutex, NULL);
    pthread_t tid;
    pthread_create(&tid, NULL, threadFunc, (void *)&shareRes);
    struct timeval Begtim, Endtim;
    gettimeofday(&Begtim, NULL);
    for (int i = 0; i < NUM; ++i)
    {
        pthread_mutex_lock(&shareRes.mutex);
        shareRes.count++;
        pthread_mutex_unlock(&shareRes.mutex);
    }
    pthread_join(tid, NULL); // 相当于进程的wait
    gettimeofday(&Endtim, NULL);
    printf("total time = %ld us\n", 1000000 * (Endtim.tv_sec - Begtim.tv_sec) + Endtim.tv_usec - Begtim.tv_usec);
    printf("num = %d\n", shareRes.count);
    pthread_mutex_destroy(&shareRes.mutex);

    


}