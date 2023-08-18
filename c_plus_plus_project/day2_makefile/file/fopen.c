#include<stdio.h>
#include<c43func.h>
int main(int argv, char *argc[])
{
    ARGS_CHECK(argv, 2); // 使用宏函数来简化重复操作
    FILE *fp = fopen(argc[1], "a+"); // 以追加的方式去写文件
    ERROR_CHECK(fp, NULL, "openfile");
    char s[10] = "helloword";
    fread(s,1,9,fp); // 读是从开头读
   printf("读到的位置:%ld",ftell(fp));
    fseek(fp,0,SEEK_SET);
     fwrite(s,1,9,fp); // 写是追加 
   printf("写到的位置:%ld",ftell(fp));

    printf("%s",s);
}