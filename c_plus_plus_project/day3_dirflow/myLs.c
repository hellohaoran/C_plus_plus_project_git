#include<c43func.h>
int main(int argc,char *argv[]){
    ARGS_CHECK(argc,2);
    DIR *dirp = opendir(argv[1]);
    ERROR_CHECK(dirp,NULL,"opendir");
    struct dirent *  direle ;
    long loc=0;
    telldir(dirp);
    while((direle=readdir(dirp)) != NULL){
        if(strcmp(direle->d_name ,"..") == 0){
            loc = telldir(dirp);
        }
      
    printf("inode:%ld recordlength:%d type:%c dirname:%s \n",direle->d_ino,direle->d_reclen,direle->d_type,direle->d_name);
    }
   
    seekdir(dirp,loc);
    puts("-----------------------");
    direle = readdir(dirp);
    printf("inode:%ld recordlength:%d type:%c dirname:%s \n",direle->d_ino,direle->d_reclen,direle->d_type,direle->d_name);
    
    closedir(dirp);
  
    
}