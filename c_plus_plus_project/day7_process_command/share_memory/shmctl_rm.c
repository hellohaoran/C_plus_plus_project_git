#include<c43func.h>
int main(){
    int shmid = shmget(1000,4096,IPC_CREAT|0600);
    char*  ret =(char*) shmat(shmid, NULL, 0);
    struct shmid_ds stat;
    
    int iret = shmctl(shmid, IPC_RMID, &stat); // IPC_RMID 标记要删除 
    ERROR_CHECK(iret, -1,"shm rm");
    sleep(20);
    shmdt(ret); // 将之从虚拟内存中删除; 

}