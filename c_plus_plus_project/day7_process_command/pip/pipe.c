#include <c43func.h>
int main()
{
    //
    int pifd1[2];
    int pifd2[2];
    int a = pipe(pifd1);
    int b = pipe(pifd2);
    ERROR_CHECK(a, -1, "pipe");
    ERROR_CHECK(b, -1, "pipe");
    // pifd1 子写父读
    // pifd2 父写子读
    if (fork() == 0)
    {
        close(pifd1[0]); // 子读关闭
        close(pifd2[1]); // 子写关闭
        write(pifd1[1], "msg from child\n", strlen("msg from child\n"));
        char buf[1024] = {0};
        read(pifd2[0], buf, 1024);
        printf("%s", buf);
    }
    else
    {
        close(pifd1[1]); // pifd1 父写关闭
        close(pifd2[0]); // pifd2 父读关闭
        char buf[1024] = {0};
        read(pifd1[0], buf, 1024);
        printf("%s", buf);
        write(pifd2[1], "msg from father\n", strlen("msg from father\n"));
        wait(NULL);
    }
}