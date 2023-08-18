#include<c43func.h>
int main(){
    // 用于创建epoll文件对象
    int epfd = epoll_create(1);//曾经参数表示监听集合的大小 ;现在无用;
    ERROR_CHECK(epfd , -1 ,"epoll_creat");
    printf("epfd = %d\n",epfd);
    close(epfd);
    // 可以监听读事件, 写事件, 异常事件; epoll_ctl ; 这里主要是监听读事件
    //epoll_wait 陷入阻塞
     

}