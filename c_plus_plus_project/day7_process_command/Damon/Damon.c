#include<c43func.h>
void Damon(){
if(fork() != 0){ // 关掉父进程 ;因为父进程作为进程组组长 不能创建新的会话;
//守护进程是脱离控制终端的;即使会话关闭也要运行;
        exit(0);
    }// 父进程关闭
    // 以下代码子进程运行; 守护进程是孤儿进程
    for(int i =0; i<3;i++){
        close(i);// 关掉文件描述符
    }
    chdir('/');
    umask(0);  // 将 父进程的掩码设置为 0 
}
int main(){
    Damon();
      for(int i =0 ; i< 1000;i++){
    time_t now = time(NULL); 
    struct  tm  * _time= localtime(&now);
    // 对系统日志的调用 
    syslog(LOG_INFO,"year = %4d, mounth = %2d, hour = %2d,min = %2d , sec = %2d\n", _time->tm_year+1900, _time->tm_mon+1,_time->tm_hour, _time->tm_min,_time->tm_sec);
sleep(2); // 睡两秒 
    }
 

    
}