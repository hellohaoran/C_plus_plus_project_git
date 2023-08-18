#include<c43func.h>
typedef struct msgbuf{
    long mtype;
    char mtext[256];
}myMsg_t;// 区分发送给谁
int main(){
    int msgid = msgget(100,IPC_CREAT|0600);
    myMsg_t msg1; // 给
    myMsg_t msg2;
    myMsg_t msg3;
    
    msg1.mtype = 1;
    strcpy(msg1.mtext ,"ganenguoqu, weilairenshijiarne");
    msg2.mtype = 2;
    strcpy(msg2.mtext, "skr skr~");
    msg3.mtype = 3; 
    strcpy(msg3.mtext, "kaikaile");
    msgsnd(msgid, &msg1, sizeof(msg1.mtext),0);
    msgsnd(msgid, &msg2, sizeof(msg2.mtext),0);

    msgsnd(msgid, &msg3, sizeof(msg3.mtext),0);


}