#include<c43func.h>
int main(){
    int num= 1000000;
    int shmid =  shmget(1000,4096,IPC_CREAT|0600);  // 4096 = 512 字节;
    int*t = (int *) shmat(shmid, NULL,0 );
    //以下是dekker的算法保持互斥
    t[0] =0 ; // wanstoenter [0] = false
    t[1] = 0;// wanstoenter [1] = false
    t[3] = 0;// turn = 0
    t[4] = 0;
    if(fork() == 0){
        for(int i=0 ;i<num; ++i){
            t[0] =1;
            while(t[1]){
              if(t[3] !=0){
              t[0] = 0;
              while(t[3] != 0){
               
              }
                t[0] =1;
              }
            }
            t[4] ++; 
            t[3] = 1;
            t[0] = 0;
          
        }
    }else{
    for(int i =0 ;i<num;++i){
      t[1] = 1;
      while(t[0]){
        if(t[3] !=1){
            t[1] = 0;
            while (t[3] != 1)
            {
               
            }
            t[1] = 1;
            
        }
      }
      t[4] ++;
      t[3] =0;
      t[1] = 0;
    }
    wait(NULL);
    printf("%d\n",t[4]); 

}
shmdt(t);

shmctl(shmid , IPC_RMID, NULL);

}