#include <c43func.h>
int main(int argc, char *argv[])
{
ARGS_CHECK(argc,2);
FILE* fp = fopen(argv[1],"rb+");
ERROR_CHECK(fp, NULL, "fopen");
int fd = fileno(fp);
printf("fd = %d\n", fd);
char buf[128] = {0};
read(fd, buf, 5);
printf("buf = %s\n", buf);
//使用read接口也是能够正常读取内容的
return 0;
}