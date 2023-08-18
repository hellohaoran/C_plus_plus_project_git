// #include<c43func.h>
// int main(int argc,char *argv[]){
//     ARGS_CHECK(argc,2);
//     DIR *dirp = opendir(argv[1]);
//     ERROR_CHECK(dirp,NULL,"opendir");
//     struct dirent *  direle ;

//     struct stat  statbuf;
//     int ret = chdir(argv[1]); // 转到 argv[1] 目录下
//     ERROR_CHECK(ret,-1,"chdir");
//     while((direle=readdir(dirp)) != NULL){
//       ret=stat(direle->d_name,&statbuf);
//       ERROR_CHECK(ret,-1,"stat");

//         int  i =0;
//         char s[11] = {'\0'};
//          int k = 1;
//         while(i<9){
//          if(k & statbuf.st_mode){
//             switch(k){
//               case 1:s[8-i] = 'x';
//                       break;
//               case 2:s[8-i] = 'w';
//                     break;
//               case 4: s[8-i] = 'r';
//                     break;
//               case 8: s[8-i] = 'x';
//               break;
//                  case 16: s[8-i] = 'w';
//               break;
//                  case 32: s[8-i] = 'r';
//               break;
//                  case 64: s[8-i] = 'x';
//               break;
//                  case 128: s[8-i] = 'w';
//               break;
//                    case 256: s[8-i] = 'r';
            
//               break;
                
//             }
//             }
//           else{
//             s[8-i] = '-';
//             }
//           k = k<<1;
//           // printf("%d\n",k);
//           i++;
//           }
//           // printf("%s\n",s);
//           printf("%s %ld %s %s %9ld %s %s \n",s,statbuf.st_nlink
//         ,getpwuid(statbuf.st_uid)->pw_name,getgrgid(statbuf.st_gid)->gr_name,statbuf.st_size,ctime(&statbuf.st_mtime),direle->d_name);
//         }
       
//      closedir(dirp);
//     }
#include<c43func.h>
int main(int argc , char *argv[]){
   ARGS_CHECK(argc, 2);
   DIR*dirp = opendir(argv[1]);
   struct dirent * direle ;
   struct stat  statbuf;
   chdir(argv[1]);
   while((direle =readdir(dirp)) != NULL){
      printf("%s\n",direle->d_name); // 名字
      stat(direle->d_name ,&statbuf );
      printf(" %d %ld %s %s %d %d %d %d %d   %s  ",statbuf.st_mode, statbuf.st_nlink, getpwuid(statbuf.st_uid)->pw_name ,
      getgrgid(statbuf.st_gid)->gr_name,localtime(&statbuf.st_mtime)->tm_year+1900 ,localtime(&statbuf.st_mtime)->tm_mon,localtime(&statbuf.st_mtime)->tm_mday ,localtime(&statbuf.st_mtime)->tm_hour,localtime(&statbuf.st_mtime)->tm_min, direle->d_name );

   } 
   closedir(dirp);

}

    

   
  
    
