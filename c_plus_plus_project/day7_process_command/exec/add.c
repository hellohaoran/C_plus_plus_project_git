#include<c43func.h>
int main(int argc,char * argv[]){
    int lhs= atoi(argv[1]);
    int rhs = atoi(argv[2]);
     printf("%d\n",lhs+rhs);
    printf("after exec pid = %d, ppid = %d",getpid(), getppid());
    return 0;
}