#include"threadPool.h"
#include<c43func.h>
//14 线程池的退出:  创建子进程和主进程 ; 通过管道 用信号机制进行通信;  
int exitPipe[2];
void sigFunc(int signum){// 信号函数
    printf("signum = %d\n", signum);
    write(exitPipe[1], "1", 1); 
    printf("Parent process is going to die!\n");
}
int main(int argc , char *argv[]){
    // ./ server 192.168.77.129 1234 3
    ARGS_CHECK(argc ,4);
    pipe(exitPipe) ;  // 建立管道作为两进程的通信; 
    if(fork ()!= 0){ // 父进程: 先注册一个信号,等待子进程的终止,最后自己终止;
        // 父进程: 1.递送信号

        close(exitPipe[0]);
        // 给子进程发送结束信号;
        signal(SIGUSR1, sigFunc); 
        // 等待子进程的终止;
        wait(NULL);
        exit(0);
    }
    //子进程: 是线程池
    close(exitPipe[1]);// 子进程关闭写的管道; 
    int workerNum = atoi(argv[3]) ; 
    threadPool_t threadpool;
    // 1.初始化 线程; 以及任务队列
    threadPoolInit(&threadpool, workerNum);
    // 2.启动多个子线程;
    makeWorker(&threadpool); 
    int sockFd;
    tcpInit(&sockFd,argv[1], argv[2]);
    // 3.将sockFd,用epoll监听
    int epFd = epoll_create(1);
    epollAdd(sockFd,epFd); // 用epoll把sockFd监听起来
    epollAdd(exitPipe[0],epFd); // 将父进程给它发送结束信号的管道 监听起来;
    // 4.创建就绪集合
    struct epoll_event readyArr[3];
    while(1){
        int readyNum = epoll_wait(epFd,readyArr, 3,-1);
        for(int i =0;i<readyNum; ++i){
            if(readyArr[i].data.fd == sockFd){
                // 5.如果有链接, 进行accept 得到全连接
                int netFd = accept(sockFd, NULL, NULL);
                // 6.子线程为了子进程的顺序执行: 不能并发; 所以要对资源加锁; 以及条件变量的等待 转work.c
                // 7.netFd会扩容readyArr
                // 先加锁
                pthread_mutex_lock(&threadpool.taskQueue.mutex);
                taskEnqueue(&threadpool.taskQueue, netFd); // 生产一个任务
                printf("New task!\n");
                // 11.唤醒 唤醒队列的线程 由于条件变量有锁保护 以区分线程是否处于空闲还是忙
                pthread_cond_signal(&threadpool.taskQueue.cond);
                // 唤醒之后子进程加锁
                // 12. 加锁之前, 主线程先解锁
                
                pthread_mutex_unlock(&threadpool.taskQueue.mutex);


            }else if(readyArr[i].data.fd == exitPipe[0]){
                printf("child process , threadPool is going to die\n");
                // for(int j=0; j<workerNum;++j){
                //     pthread_cancel(threadpool.tid[j]);// 将子线程结束掉
                // }
                // 以下是优雅退出
                threadpool.exitFlag = 1;
                pthread_cond_broadcast(&threadpool.taskQueue.cond) ;  // 给所有在任务队列的线程发送唤醒信号
                for(int j =0;j< workerNum; ++j){
                    pthread_join(threadpool.tid[j], NULL);// 回收子进程的资源
                }
                // 主线程结束 ; 
                pthread_exit(NULL);
            }
        }

    }
}
int threadPoolInit(threadPool_t * pThreadPool , int workerNum){
    pThreadPool->threadNum = workerNum;
    pThreadPool->tid = (pthread_t*)calloc(workerNum,sizeof(pthread_t));
    pThreadPool->taskQueue.pFront = NULL;
    pThreadPool->taskQueue.pRear = NULL;
    pThreadPool->taskQueue.size = 0;
    pthread_mutex_init (&pThreadPool->taskQueue.mutex, NULL);
    pthread_cond_init(&pThreadPool->taskQueue.cond ,NULL);
    pThreadPool->exitFlag = 0;

}