#include<c43func.h>
#define N 2000000;
int main(){
    int semArrid = semget(1000,1,IPC_CREAT|0600);
ERROR_CHECK(semArrid,-1,"semget");
int ret = semctl(semArrid,0,SETVAL,1);
ERROR_CHECK(ret,-1,"semctl");
struct sembuf P;
P.sem_num = 0;//信号量值在集合中的下标
P.sem_op = -1;//信号量值修改
P.sem_flg = SEM_UNDO;//如果P操作被终止，会自动恢复
struct sembuf V;
V.sem_num = 0;
V.sem_op = 1;
V.sem_flg = SEM_UNDO;
int shmid = shmget(1000,4096,IPC_CREAT|0600);
int *p = (int *)shmat(shmid,NULL,0);
p[0]=0;
struct timeval beg,end; // 設置開始與結束時間
gettimeofday(&beg,NULL);  // 將开始时间注册
if(!fork()){
for(int i =0; i < N ++i){
semop(semArrid,&P,1);
++p[0];
semop(semArrid,&V,1);
}
exit(0);
}
else{
for(int i =0; i < N ++i){
semop(semArrid,&P,1);
++p[0];
semop(semArrid,&V,1);
}
wait(NULL);
gettimeofday(&end,NULL); //设置结束时间
time_t s = end.tv_sec - beg.tv_sec; //时间进行读取
time_t us = end.tv_usec - beg.tv_usec; // 时间进行读取
if(us < 0){
us = us + 1000000;
--s;
}
printf("total time = %ld s %ld us\n", s, us);
printf("p[0] = %d\n", p[0]);
}
return 0;
}