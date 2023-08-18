#include<c43func.h>
int main(){
    int shmid = shmget(1000,4096,IPC_CREAT|0600);
    // int ret = shmat(shmid, NULL, 0);
    struct shmid_ds stat;
    
    shmctl(shmid, IPC_STAT , &stat);
    printf("共享内存的 perm = %o\n", stat.shm_perm.mode);
    printf("共享内存的 大小 %lu\n", stat.shm_segsz);
    
    stat.shm_perm.mode = 0666;
    shmctl(shmid,IPC_SET, &stat); 


}