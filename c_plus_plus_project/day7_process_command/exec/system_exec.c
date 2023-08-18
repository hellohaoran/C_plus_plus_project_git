#include<c43func.h>
int main(int argc, char* argv[]){
    char * word=NULL;
    // char * _word;
    char * word_cnt[10] = {NULL};
    int i = 0;
    char buf[1024] = {0};
    strcpy(buf, argv[1]);
    word = strtok(buf, " "); 
    word_cnt[i] = (char*)malloc(sizeof(word)+1);
    strcpy(word_cnt[i], word);
    i++;
    while(word){
    word = strtok(NULL, " ");
    if(word == NULL){
        continue;
    }
    word_cnt[i] = (char*)malloc(sizeof(word)+1);
    strcpy(word_cnt[i], word);
    i++;
    }
//    char name[10]={0};
//    int j =2;
//    printf("%s",word_cnt[0]);
//    word = NULL;
//    word_cnt[0][sizeof(word_cnt[0])+1] = '\0';
//    strcpy(word,word_cnt[0]);
//    for(int i=0;word[--j]!= '\0';++i){
//     name[i]= word[j++];
    
//    } // 定义好名字 
// name[] = 0;
// printf("%s\n",name);
    word = (char*)malloc(sizeof(word_cnt[0])); // 字符串使用之前一定要开辟空间

int j = 2 ;
    for(int k =0;word_cnt[0][j]!= '\0';++k ){
        word[k] = word_cnt[0][j];
        j++;
    }
    // word[strlen(word)+1] = 0;
// strcpy(word,&word_cnt[0][2]);

    if(fork() == 0){
         srand(time(NULL));
        int t = rand()%50 +15;
        printf("%d\n",t);
        execl(word_cnt[0],word_cnt[0],word_cnt[1],word_cnt[2],NULL );
       

    }else{
        sleep(2);
    }
// execl("add","./add","7","8",NULL);

}