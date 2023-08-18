#include <c43func.h>
int main(int argc, char *argv[])
{
    // ./chat1 pip1 pip2
    ARGS_CHECK(argc, 3);
    int fdw = open(argv[1], O_WRONLY);
    int fdd = open(argv[2], O_RDONLY);

    puts("pip start!");
    // 全双工通信
    char buf[4096] = {0};
    // 以下是I/O多路复用
    fd_set rdset; // 设置监听集合
    while (1)
    {
        // 先读
        FD_ZERO(&rdset);              // 将集合设为 初始化
        FD_SET(STDIN_FILENO, &rdset); // 将STDIN 的文件描述符加入集合
        FD_SET(fdd, &rdset);          // 将fdd 加入描述符
        struct timeval timeout;
        timeout.tv_sec = 2;
        timeout.tv_usec = 50000;
        int rets = select(fdd + 1, &rdset, NULL, NULL, &timeout); // select 会将rdset的内容改变;
        if (rets == 0)
        {
            puts("time out");
            continue;
        }
        if (FD_ISSET(STDIN_FILENO, &rdset))
        {
            puts("msg from  STDIN ready write \n");
            memset(buf, 0, sizeof(buf));
            int ret = read(STDIN_FILENO, buf, sizeof(buf));
            if (ret == 0)
            {
                write(fdw, "结束了!\n", sizeof("结束了!\n"));
                break;
            }
            write(fdw, buf, strlen(buf));
        }
        if (FD_ISSET(fdd, &rdset))
        {
            // 后写 ; 写之前从键盘里读取数据
            puts("msg of read pip   ready\n");
            memset(buf, 0, sizeof(buf));
            int ret = read(fdd, buf, sizeof(buf));
            if (ret == 0)
            {
                printf("end session!\n");
                break;
            }
            puts(buf);
        }
    }
}