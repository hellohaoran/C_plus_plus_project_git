#include<c43func.h>
int main(){
    uid_t uid = getuid();
    uid_t euid = geteuid();
    printf("uid = %d, euid = %d\n",uid, euid);
    pid_t  pid =  getpid();
    printf("pid = %d",pid);
}