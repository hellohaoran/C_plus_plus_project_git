#include<c43func.h>
int main(int argc,char * argv[]){
pid_t pid = getpid();
pid_t ppid = getppid();
printf("pid = %d\n",pid);
printf("ppid = %d\n",ppid);

}