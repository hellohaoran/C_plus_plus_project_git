#include<c43func.h>
#include"head.h"
int sendFd(int pipeFd , int fdTosend, int exitflag){ // pipeFd 是管道描述符, fdtosend 是要被发送的描述符
    //发送描述符
    struct msghdr hdr ;
    bzero(&hdr , sizeof(hdr));
    //第一个部分发送文本数据
    struct iovec iov[1]; // 长度为1时 ,离散数据退化成连续数据
    // 发送exitflag 给另一个进程 
    iov[0].iov_base = &exitflag;
    iov[0].iov_len =sizeof(int) ;
    hdr.msg_iov = iov;
    hdr.msg_iovlen = 1 ; 
    //第二个部分发送控制数据
    struct cmsghdr * pcmsghdr = (struct cmsghdr *)calloc(1 , CMSG_LEN(sizeof(int)) );
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
// int sendFd(int pipeFd , int fdTosend){
//     struct msghdr hdr;
//      struct iovec iov[1];
//      char buf[] = "hello";
//      // 传递信息
//      iov[0].iov_base = buf;
//      iov[0].iov_len = sizeof(buf);
//      hdr.msg_iov = iov;
//      hdr.msg_iovlen =1 ; // 在iov的有几个元素
//     //  struct cmsghdr pcmsg;// 不能在栈上分配
//     // CMSG_LEN()表示
//     // 控制信息
//     struct cmsghdr *pcmsg = (struct cmsghdr *) calloc(1,sizeof(CMSG_LEN(sizeof(int)))); 
//     pcmsg->cmsg_level= SOL_SOCKET;
//     pcmsg->cmsg_len = CMSG_LEN(sizeof(int)) ; //有多长
//     pcmsg->cmsg_type = SCM_RIGHTS ; // 进程间传递描述符的类型
//     *(int*)CMSG_DATA(pcmsg)  =  fdTosend;
//     hdr.msg_control = pcmsg ;
//     hdr.msg_controllen = CMSG_LEN(sizeof(int)) ;
//     int ret = sendmsg(pipeFd , &hdr, 0);
//     ERROR_CHECK(ret ,-1, "sendmsg");  
//     return 0;
//     }
int recvFd(int pipeFd , int * pFdToRecv , int * pExitFlag){ // pipeFd 是管道描述符, 要改变收到描述符的值 是要被发送的描述符
    //发送描述符
    struct msghdr hdr ;
    bzero(&hdr , sizeof(hdr));
    //第一个部分发送文本数据
    struct iovec iov[1]; // 长度为1时 ,离散数据退化成连续数据
    
    iov[0].iov_base = pExitFlag;
    iov[0].iov_len = sizeof(int); // 不能赋为 0 ;
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
    ERROR_CHECK(ret , -1 , "recvmsg");
    *pFdToRecv = *(int *)CMSG_DATA(pcmsghdr) ;
    return 0 ; 
}
