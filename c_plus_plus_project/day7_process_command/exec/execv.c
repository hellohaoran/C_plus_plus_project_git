#include<c43func.h>
int main(){
    printf("before exec ! pid = %d, ppid = %d\n",getpid(), getppid());
    char * argvector[] = {"./add","15","75",NULL};
    // execv("add",argvector);
    printf("after execl !"); // 不会执行,因为代码段, 堆 , 栈 数据段 会被清空;
    char str_[10] ="hj sd ki ";
    char * st_[5] ={0} ;
     char st[4] = {0};
    int h= 0;
    for(int i =0 ; i<strlen(str_); ){
        int j =i; 
        if(str_[j] != ' ' ){ //  切割字符串
        int k=0;      
        for(; str_[j] != ' ';++j){
                
            st[k++] = str_[j];
            }
            st[k] = '\0';
            // printf("%s\n",st);  


            //st_[h]  = st; // st_[h] 只是记得住名字 ; 由于 重复写; 最后 只是将最后一次写到st_[h]里面 
          
            // st_[h] = (char*)malloc(sizeof(st+1));
            // strcpy(st_[h], st);
          
            // st_[h] = strdup( st);  // 这种方法是将 st 的副本 给 st_[h]
            h = h+1;
            i = j ;
            }else{
                i++;
            }
    }
for(int i =0;i<h;++i){
        printf("%s\n", st_[i]);
    }
    


}