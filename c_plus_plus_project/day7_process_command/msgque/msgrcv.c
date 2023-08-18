#include<c43func.h>
typedef struct msgbuf{
    long mtype;
    char mtext[256];
}myMsg_t;// 区分发送给谁
int main(){
    printf("who are you 1.huangxiaoming 2.wuyifan 3.caixukun\n");
    int msqid = msgget(100,IPC_CREAT|0600); // 若已经存在这个消息队列; 则 从这个消息队列读
    ERROR_CHECK(msqid, -1 ,"msgget");
    long type;


printf("you have three chances\n");
for(int i =0 ; i<3;++i){
    scanf("%ld",&type);
struct msgbuf   msg;
memset(&msg,0,sizeof(msg));
// 将消息重写到msg.mtext
int ret = msgrcv(msqid,&msg,sizeof(msg.mtext),type, 0);  // 没有消息立即返回
ERROR_CHECK(ret,-1 ,"msgrcv");
printf("you are %ld , msg = %s\n", msg.mtype, msg.mtext);
}


}