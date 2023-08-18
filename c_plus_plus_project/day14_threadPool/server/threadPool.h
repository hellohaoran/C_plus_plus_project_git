#include<c43func.h>
//设计线程池的数据结构
/*
主线程 当有链接来到时; 如果队列不满将netFd 加入到任务队列; 
子线程 当队列不空时,取出netFd 进行与客户端的通信
*/
typedef struct task_s{
int netFd; // 传递文件描述符(从主线程传递到子线程)
struct task_s *pNext;  
}task_t; // 任务类型 是链表来构建任务队列
// 原来的进程池的sendFd 是入队的操作; 进程池的recvFd是出队的操作;
typedef struct taskQueue_s
{
task_t * pFront ; // 队首指针
task_t * pRear; // 队尾的指针
int size ; // 队列现在的长度
pthread_mutex_t mutex;// 队列共享需要加锁 保护任务队列
pthread_cond_t cond;// 条件变量也要参加, 使之可以主线程与子线程区分先后的顺序; 

}taskQueue_t;

// 定义队列
typedef struct threadPool_s
{
    pthread_t *tid; //子线程数组
    int threadNum ; //子线程的数量 
    taskQueue_t taskQueue; // 加一个任务队列->主线程与子线程共享的任务队列是一个连表类型
    int exitFlag; // 用于退出线程的标志位
}threadPool_t;
int taskEnqueue(taskQueue_t * pTaskQueue, int netFd);
int taskDequeue(taskQueue_t * pTaskQueue);
// 用来初始化线程: 即要申请多少个子线程
int threadPoolInit(threadPool_t * pThreadPool , int workerNum); 
// 初始化tcp连接
int tcpInit(int *pSockFd , char * ip, char *port) ;
//加入epoll监听; 
int epollAdd(int fd, int epfd);
int epollDel(int fd, int epfd); 
int sendFile(int netFd) ; 
int makeWorker(threadPool_t *pThreadPool); 