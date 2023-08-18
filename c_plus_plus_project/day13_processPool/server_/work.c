// 创建子进程的函数, 参数是多少个子进程
// 要有子进程自己的数据结构
#include"worker.h"
#include"head.h"
int makeChild(workerData_t * workerArr,int workerNum  ){
    pid_t pid;
    int pipFd[2];

    for(int i = 0;i< workerNum ; ++i){
        socketpair(AF_LOCAL , SOCK_STREAM , 0 , pipFd) ; // socket 管道双方进程可以通信// 每次循环,主进程都增加一个进程描述符
        pid = fork(); // fork创建子进程,返回值是pid ,  pid == 0 是子进程 , pid == 子进程的pid 是给父进程返回的
        if(pid == 0){
            // 子进程处理函数
            // 子进程, 确保不会脱离if结构
            close(pipFd[1]);
            eventHandler(pipFd[0]);
        }
        // 父进程
        close(pipFd[0]);
        printf("pipeFd = %d, pid = %d\n", pipFd[1] , pid);
        workerArr[i].pid = pid;
        // 将父进程与子进程通信的管道明确
        workerArr[i].pipfd = pipFd[1];
        workerArr[i].status = FREE;
    }
} 
int eventHandler(int pipFd){
    while(1){
        int netFd ;
        // 子进程接收主进程发过来的已连接socket描述符
        int exitFlag ;
        // 从父进程收到netFd, exitFlag
        // 这里用了从父进程收到消息; exitFlag;
        recvFd(pipFd, &netFd, &exitFlag) ;
          if(exitFlag == 1){
            puts("I am going to exit");
            exit(0);
        }
        printf("I got a task\n");
         //recvFd就绪
        sendFile(netFd) ;  
        printf("I have done this task\n");
        // 子进程做完事情了
        // 需要往主进程发送消息 ; 好让主进程知道 , 结果是父进程的管道会就绪
        
        pid_t pid = getpid(); 
        write(pipFd, &pid , sizeof(pid));
        
        close(netFd); 
       
    }
}