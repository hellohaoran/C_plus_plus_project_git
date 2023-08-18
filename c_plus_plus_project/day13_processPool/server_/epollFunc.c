 #include<c43func.h>
int epollAdd(int fd, int epfd){
    struct epoll_event event ;
    event.events = EPOLLIN;
    event.data.fd = fd ;
    int ret = epoll_ctl(epfd , EPOLL_CTL_ADD, fd, &event); // 加入监听
    ERROR_CHECK(ret , -1 , "epoll_ctl");
    return 0 ; 
}
int epollDel(int fd, int epfd){
    struct epoll_event event ;
    event.events = EPOLLIN;
    event.data.fd = fd ;
    int ret = epoll_ctl(epfd , EPOLL_CTL_DEL, fd, &event);   // 删除监听
    ERROR_CHECK(ret , -1 , "epoll_ctl");
    return 0 ; 
}
