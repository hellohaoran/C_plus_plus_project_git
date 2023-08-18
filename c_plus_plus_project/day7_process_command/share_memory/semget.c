#include<c43func.h>
int main(){
    int num= 1000000;
    int shmid =  shmget(1000,4096,IPC_CREAT|0600);  // 4096 = 512 字节;
    int*t = (int *) shmat(shmid, NULL,0 );
   
    t[0] =0 ; // wanstoenter [0] = false
    int semid = semget(1000,1,IPC_CREAT|0600);  // 创建信号量
    int ret = semctl(semid,0,SETVAL,1);
    ERROR_CHECK(ret  ,-1 ,"Ssemctl_setval");
    ret = semctl(semid,0,GETVAL ); 
    ERROR_CHECK(ret , -1 , "semctl_getval");
    // printf("sem = %d", ret);
    struct sembuf P;
    struct sembuf V;
    P.sem_num = 0;// 对要操作的信号量的下标
    P.sem_flg = SEM_UNDO; // 设置操作标志
    P.sem_op =-1; // 对资源的影响
    V.sem_num = 0;
    V.sem_flg = SEM_UNDO;
    V.sem_op = 1;
    struct timeval timeBeg, timeEnd;
    gettimeofday(&timeBeg,NULL);

    if(fork() == 0){
        for(int i=0 ;i<num; ++i){
          semop(semid,&P,1);
        t[0]++;
          semop(semid,&V,1);
          
        }
    }else{
    for(int i =0 ;i<num;++i){
             semop(semid,&P,1);
        t[0]++;
          semop(semid,&V,1);
    }
    wait(NULL);
    printf("%d\n",t[0]); 

}
    gettimeofday(&timeEnd,NULL);

printf("%ld\n",timeBeg.tv_usec-timeEnd.tv_usec);
shmctl(shmid , IPC_RMID, NULL);
shmdt(t);


}