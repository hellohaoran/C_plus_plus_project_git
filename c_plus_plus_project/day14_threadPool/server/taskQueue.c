#include"threadPool.h"
int taskEnqueue(taskQueue_t * pTaskQueue, int netFd){
    // 将netFd入队

    //在堆上申请一个元素的内存
    task_t *pTask = (task_t *)calloc(1, sizeof(task_t));
    pTask->netFd =netFd;
    // 尾插法;
    //判断队列为空
    if(pTaskQueue->size == 0){
        pTaskQueue->pFront =pTask;
        pTaskQueue->pRear = pTask;
    }else{
        pTaskQueue->pRear->pNext = pTask;
        pTaskQueue->pRear = pTask;
    }
    ++pTaskQueue->size;
    return 0;
}
int taskDequeue(taskQueue_t * pTaskQueue){
    // 在队列不为空的时候才取元素
    // 队头取元素
    task_t *pCur = pTaskQueue->pFront ;
    // 队头往后面移
    pTaskQueue->pFront =pCur->pNext; 

    free(pCur);
    --pTaskQueue->size;
    return 0;
}