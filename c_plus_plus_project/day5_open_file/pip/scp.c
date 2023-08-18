#include <c43func.h>
int main()
{
    int fds[2] = {0};
    int rs = pipe(fds); // fds[0]是读 fds[1]是写
    ERROR_CHECK(rs, -1, "pipe");
    char buf[1024] = {0};
    if (fork() == 0)
    {
        // 子读管道;写文件
        close(fds[1]);
        int fw = open("file2", O_CREAT | O_RDWR | O_TRUNC, 0666); // 打开文件
        while (1)
        {
            bzero(buf, sizeof(buf));
            int res = read(fds[0], buf, sizeof(buf));
            if (res == 0)
            {
                // 当父进程的写管道关闭就 退出循环
                break;
            }

            write(fw, buf, res); // 写到到fw里面去
        }
        close(fds[0]);
    }
    else
    {
        // 父读文件,写管道
        close(fds[0]); // 关闭读管道
        int fr = open("file1", O_RDWR | O_CREAT);
        while (1)
        {
            bzero(buf, sizeof(buf));
            int ret = read(fr, buf, sizeof(buf));
            if (ret == 0)
            {
                // 如果读到终止就
                break;
            }
            write(fds[1], buf, ret);
        }
        close(fds[1]); // 父进程关闭写端,子进程的读管道会返回0
        wait(NULL);    //
    }
}