#include<c43func.h>
int main(){
    key_t k =ftok("./file1",1);
    ERROR_CHECK(k,-1,"ftok");
    printf("ipc key = %d\n",k);
    int shm = shmget(k,4096,IPC_CREAT|0600);
    char* ret = shmat(shm,NULL,0);
    ERROR_CHECK(ret,(void*)-1,"shm");
    // strcpy(ret, "hello");
    printf("shm id = %d\n",shm);
    printf("%s",ret);

}