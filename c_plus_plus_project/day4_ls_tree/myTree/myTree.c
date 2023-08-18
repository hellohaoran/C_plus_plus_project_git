#include<c43func.h>
void DFS(char *path,int size){
    DIR* dirp = opendir(path);
    struct dirent * direle;  
    char newPath[1024] = {0};
    while ((direle = readdir(dirp)) != NULL)// 直到没有文件
    {
        if((strcmp(direle->d_name,".") == 0)   || strcmp(direle->d_name , "..") == 0 ){
            continue;
        }
        for(int i =0;i<size;++i){
               printf("-");
            }
        puts(direle->d_name);

        if(direle->d_type == DT_DIR){ // 是目录类型的文件 
            sprintf(newPath,"%s%s%s",path,"/",direle->d_name);
           
            printf("%s\n",newPath);
            DFS(newPath,size+4);
        }
    }
    
}
int main(int argc, char *argv[]){
    ARGS_CHECK(argc,2);
    puts(argv[1]);
    DFS(argv[1],4);
}