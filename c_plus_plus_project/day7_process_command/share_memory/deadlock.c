#include<c43func.h>
#define N 10000000
int main(){
    //生产者消费者;模型
    //逻辑生产者消耗仓库, 生产商品;
    // 消费者消耗商品,生产仓库
int shmid = shmget(1000, 4096, IPC_CREAT|0600);
int *t=(int*)shmat(shmid,NULL,0);//将 申请的物理的空间添加到文件系统
t[0] = 10; // t[0]表示仓库的个数
t[1] = 0;// t[1] 表示商品的个数 
int smid = semget(10001,1, IPC_CREAT|0600); // 创建信号量
int ret = semctl(smid,0,SETVAL,1);
struct sembuf P,V;
P.sem_num = 0;
P.sem_flg = 0;
P.sem_op = -1;
V.sem_flg = 0;
V.sem_num = 0;
V.sem_op  = 1;
if(fork() == 0){//多生产;单消费者模型 
 //子进程主要是生产者; 消耗仓库,生产商品
 while(1){
        semop(smid,&P,1);
 if(t[0]>0){
    printf("before produce , space %d, good %d\n, total = %d", t[0],t[1], t[0]+t[1]);

    t[0]--;
    t[1]++;
   
    printf("after produce , space %d, good %d\n,total = %d ", t[0],t[1], t[0]+t[1]);
     sleep(1);
 }
  semop(smid,&V,1);

 }
}
else{ //父进程主要是消费者; 消耗商品,生产仓库
while(1){ 
    semop(smid,&P,1);
 if(t[1]>0){ 
    printf("before consum , space %d, good %d , total = %d\n", t[0],t[1],t[0]+t[1]);

    t[1]--;
    t[0]++;

    printf("after consum , space %d, good %d , total = %d\n", t[0],t[1],t[0]+t[1]);
    
 }
     semop(smid,&V,1);


}



}
shmctl(shmid,IPC_RMID, NULL );
shmdt(t);

}


