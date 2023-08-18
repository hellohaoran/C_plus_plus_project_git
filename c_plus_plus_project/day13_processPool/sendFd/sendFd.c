#include<c43func.h>
int sendFd(int pipeFd , int fdTosend){ // pipeFd 是管道描述符, fdtosend 是要被发送的描述符
    //发送描述符
    struct msghdr hdr ;
    bzero(&hdr , sizeof(hdr));
    //第一个部分发送文本数据
    struct iovec iov[1]; // 长度为1时 ,离散数据退化成连续数据
    char buf[10] ="hello";
    iov[0].iov_base = buf;
    iov[0].iov_len =5 ;
    hdr.msg_iov = iov;
    hdr.msg_iovlen = 1 ; 
    //第二个部分发送控制数据
    struct cmsghdr * pcmsghdr = (struct cmsghdr *)calloc(1 , CMSG_LEN(sizeof(int))) ;
    pcmsghdr->cmsg_len = CMSG_LEN(sizeof(int)); // 数据的长度 
    pcmsghdr->cmsg_level = SOL_SOCKET ;
    pcmsghdr->cmsg_type = SCM_RIGHTS ; // socket control message
    *(int *)CMSG_DATA(pcmsghdr) = fdTosend ; // 该函数返回承载数据的起始地址; 
    // 把以上的控制信息填到msg_control 和 msg_controllen 
    hdr.msg_control = pcmsghdr ; 
    hdr.msg_controllen = CMSG_LEN(sizeof(int));
    int ret = sendmsg(pipeFd ,&hdr , 0);
    ERROR_CHECK(ret , -1 , "sendmsg");
    return 0 ; 
}
int recvFd(int pipeFd , int * pFdToRecv){ // pipeFd 是管道描述符, 要改变收到描述符的值 是要被发送的描述符
    //发送描述符
    struct msghdr hdr ;
    bzero(&hdr , sizeof(hdr));
    //第一个部分发送文本数据
    struct iovec iov[1]; // 长度为1时 ,离散数据退化成连续数据
    char buf[10]  = {0};
    iov[0].iov_base = buf;
    iov[0].iov_len = sizeof(buf); // 不能赋为 0 ;
    hdr.msg_iov = iov;
    hdr.msg_iovlen = 1 ; 
    //第二个部分发送控制数据
    struct cmsghdr * pcmsghdr = (struct cmsghdr *)calloc(1 , CMSG_LEN(sizeof(int))) ;
    pcmsghdr->cmsg_len = CMSG_LEN(sizeof(int)); // 数据的长度 
    pcmsghdr->cmsg_level = SOL_SOCKET ;
    pcmsghdr->cmsg_type = SCM_RIGHTS ; // socket control message
    // 把以上的控制信息填到msg_control 和 msg_controllen 
    hdr.msg_control = pcmsghdr ; 
    hdr.msg_controllen = CMSG_LEN(sizeof(int));
    int ret = recvmsg(pipeFd ,&hdr , 0);
    ERROR_CHECK(ret , -1 , "sendmsg");
    *pFdToRecv = *(int *)CMSG_DATA(pcmsghdr) ;
    return 0 ; 
}
int main(){
    int sv[2];
    socketpair(AF_LOCAL, SOCK_STREAM , 0 , sv);
    // 创建两个文件对象
    
    socketpair(AF_LOCAL,SOCK_STREAM,0 , sv);

    if(fork() == 0){ //子进程
    int fd = open("file", O_RDWR) ;
    printf("child fd = %d\n", fd);
    write(fd , "hello", 5);
    sendFd(sv[1], fd);// 将fd文件对象传递给父进程
    sleep(10);
    exit(0);
    }else{ // 父进程
    int fd = open("file1", O_RDWR);
    printf("parent fd = %d\n", fd);
    int newFd;
    recvFd(sv[0], &newFd);  // 父进程收到这个子进程的传递的文件描述符 ; 复制给新的文件对象文件描述符  
    printf("parent newFd = %d\n", newFd);
    write(newFd , "world",5);  
    wait(NULL);
    }
}