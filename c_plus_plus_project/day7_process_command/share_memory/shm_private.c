#include<c43func.h>
int main(){
    int shmid = shmget(IPC_PRIVATE ,4096,IPC_CREAT|0600); // shmget 在物理内存上创建获得
    ERROR_CHECK(shmid, -1, "shmat");
    
    char*  chr= (char*)shmat(shmid,NULL,0);
    ERROR_CHECK(chr, (void *)-1, "shmat");
    if(fork() == 0){
        strcpy(chr, "hello");

    }else{
        //父进程读
        wait(NULL);
        printf("%s", chr);

    }
    shmdt(chr);
shmctl(shmid, IPC_RMID,NULL);

}