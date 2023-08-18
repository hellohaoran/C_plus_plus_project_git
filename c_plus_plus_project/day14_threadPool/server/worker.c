 #include"threadPool.h"
 #include<c43func.h>
 void cleanFunc(void *arg){
    threadPool_t * pThreadPool = (threadPool_t*) arg;
    pthread_mutex_unlock(&pThreadPool->taskQueue.mutex);  
 }
 void * handleEvent(void *arg){
    threadPool_t * pThreadPool = (threadPool_t* )arg;
    // 7.子线程启动进行加锁
    int netFd;
    while(1){
       
        printf("I am free! pthread Id = %ld\n", pthread_self());
        pthread_mutex_lock(&pThreadPool->taskQueue.mutex);
        pthread_cleanup_push(&cleanFunc, (void*)pThreadPool);// 注册清理处理函数;在线程终止之前执行清理操作;
        while(pThreadPool->taskQueue.size == 0 && pThreadPool->exitFlag == 0){
            //8. 任务队列为空进行等待
            //9.检查有无加锁, 把自己加入唤醒队列; 之后解锁并等待;
            // 其他子线程也检查有无加锁, 把自己加入唤醒队列; 之后解锁并等待; 最终锁是释放的
            pthread_cond_wait(&pThreadPool->taskQueue.cond,&pThreadPool->taskQueue.mutex);
            
        }
         if(pThreadPool->exitFlag != 0){
            printf("I am going to die child thread") ;
            pthread_exit(NULL);
        }
        // 13. 子进程苏醒 
        // 拿到队首的文件描述符
        // 将任务队列的队首删除; 在完成对队列的操作后要及时解锁
         netFd = pThreadPool->taskQueue.pFront->netFd; 
        taskDequeue(&pThreadPool->taskQueue);
        pthread_cleanup_pop(1);  // 此时执行线程清理函数;
        //之后子进程进行传输文件的任务
        printf("I am working pthread Id = %ld\n", pthread_self());
        sendFile(netFd);
        puts("done\n");
        close(netFd);
        
    }
 }

 int makeWorker(threadPool_t *pThreadPool){
    for(int i =0;i<pThreadPool->threadNum; ++i){
        // 创建子线程; handleEvent 是线程启动函数: 线程创建后,就直接执行handleEvent; 将pThreadPool 作为参数传到handleEvent
        pthread_create(&pThreadPool->tid[i], NULL, handleEvent, (void*)pThreadPool);
        // 子线程使用wait 等待主进程 传递netFd, 以及signal信号之前要对队列这个条件变量进行加锁

    }
 }