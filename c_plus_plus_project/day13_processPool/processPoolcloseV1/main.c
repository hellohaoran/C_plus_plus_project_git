#include<c43func.h>
#include"worker.h"
#include"head.h"
/*主进程: 与客户端建立连接 , 之后把accept 链接交给子进程*/
// 以下处理进程退出
// 为使 sigFunc可以知道workerArr 和 workNum 所以定义在此
workerData_t * workerArr ;
int workerNum;
void sigFunc(int signum){
    printf("signum = %d\n", signum);
    for(int i =0 ; i<workerNum ; i++){
        // 给子进程发送终结信号
        kill(workerArr[i].pid, SIGUSR1); 
    }
    for(int i =0; i <workerNum ; i++){
        wait(NULL);
    }
    puts("process pool is over !");
    exit(0);
}
int main(int argc, char*argv[]){
    // ./server 192.168.77.129 1234 3
    //创建子进程
    // 如果已经fork过了 , 怎么样让父子进程共享socket全连接队列的netFd这个文件对象
     workerNum = atoi(argv[3]);  
    // 将子进程的信息用数组存起来
   workerArr = (workerData_t * ) calloc(workerNum,sizeof(workerData_t) );
    makeChild(workerArr , workerNum);
    // 注冊10號信號；儅别的进程给主进程 发送 10号信号时 , 转到sigFunc函数 
    signal(SIGUSR1 , sigFunc);
    //初始化tcp连接
    int sockFd ; 
    tcpInit(&sockFd , argv[1] , argv[2]) ; 
    // while(1); 
    // 让主进程运行
    //用epoll 把tcp连接和子进程管理起来
    int epFd = epoll_create(1); // 建立epoll文件描述符
     // 子进程也可以通过socket管道与主进程通信 ; 所以将sock管道加入监听
     epollAdd(sockFd, epFd);
     // 将每个子进程的管道加入监听 好让子进程结束后,主进程知道
    for(int i =0 ;i<workerNum; ++i){
        epollAdd(workerArr[i].pipfd , epFd);
    }
    //就绪队列; 
    int listenSize = workerNum +1 ; // 有socket描述符和子进程的管道加入监听 
    struct  epoll_event *readyArr = (struct epoll_event *) calloc(listenSize, sizeof(struct epoll_event) ); 
    while(1){
        //造成死循環的原因; 子進程挂了 ； 則子进程的管道关闭写端; 则 父进程的读端就绪 ; epoll_wait 就绪;
        int readyNum = epoll_wait(epFd , readyArr , listenSize , -1);
        printf("epoll wait ready\n");
        for(int i =0 ; i<readyNum;++i){
            if(readyArr[i].data.fd == sockFd){
                puts("client connect");
                int netFd = accept(sockFd , NULL , NULL);
                ERROR_CHECK(netFd, -1 ,"accept");
                //之后将netFd交给子进程; 子进程须满足不忙碌 即free的条件
                for(int j=0; j<workerNum; ++j){
                    if(workerArr[j].status == FREE){
                        printf("%d worker got a job, pid = %d\n",j, workerArr[j].pid );
                        sendFd(workerArr[j].pipfd, netFd);// 把链接移交给子进程
                        close(netFd);// 并不会把网络连接给关闭; 因为子进程已经连上
                        workerArr[j].status = BUSY;
                        break; 
                    }
                }
            }
            else{
                puts("one worker finished his jobs \n");
                int j ;
                for(j =0; j<workerNum ; ++j){
                    if(readyArr[i].data.fd == workerArr [j].pipfd){ // 读就绪表示收到子进程发来的pid ; 收到子进程结束
                        pid_t  pid;
                        int ret = read(workerArr[j].pipfd,&pid, sizeof(pid));
                       
                        printf("%d worker pid = %dfinish his job\n",j, pid);
                        workerArr[j].status = FREE;
                        break;
                    }
                }
            }
        }
    }
}