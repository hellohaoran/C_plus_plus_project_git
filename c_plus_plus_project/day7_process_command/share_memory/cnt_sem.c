#include<c43func.h>
int main(){
 

int semid = semget(1002,2,IPC_CREAT|0600); // key 相同的信号量值 ; 信号量的个数也相同
printf("%d\n",semid);
int flour = semctl(semid,0,SETVAL,100);
ERROR_CHECK(flour ,-1 ,"setval_1");
int water = semctl(semid,1,SETVAL,100);
ERROR_CHECK(water ,-1 ,"setval_2");
printf("water remain = %d\n", semctl(semid,1,GETVAL));
printf("flour remain = %d\n", semctl(semid,0,GETVAL));

struct sembuf  cake[2];
cake[0].sem_num = 0; // 消耗面粉
cake[0].sem_flg= SEM_UNDO;
cake[0].sem_op = -3;
cake[1].sem_num = 1; // 消耗水
cake[1].sem_flg = SEM_UNDO;
cake[1].sem_op = -5; 
struct sembuf bread[2];
bread[0].sem_num = 0; // 消耗面粉
bread[0].sem_flg= SEM_UNDO;
bread[0].sem_op = -3;
bread[1].sem_num = 1; // 消耗水
bread[1].sem_flg = SEM_UNDO;
bread[1].sem_op = -5; 
if(fork() == 0){
    while(1){
        printf("befor make bread");
        printf("water remain = %d", semctl(semid,1,GETVAL));
        printf("flour remain = %d", semctl(semid,0,GETVAL));
        semop(semid,bread,2);
        printf("after make bread");
        printf("water remain = %d", semctl(semid,1,GETVAL));
        printf("flour remain = %d", semctl(semid,0,GETVAL));
        sleep(1);
    }
}else{
    while(1){
     printf("befor make bread");
        printf("water remain = %d", semctl(semid,1,GETVAL));
        printf("flour remain = %d", semctl(semid,0,GETVAL));
        semop(semid,cake,2);
        printf("after make bread");
        printf("water remain = %d", semctl(semid,1,GETVAL));
        printf("flour remain = %d", semctl(semid,0,GETVAL));
        
sleep(1);

    }
    wait(NULL);
}


}