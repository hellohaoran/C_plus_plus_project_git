#include<c43func.h>
int main(int argc , char* argv[]){
    // ./gethostbyname www.baidu.com
    ARGS_CHECK(argc, 2);
    struct hostent * pHost = gethostbyname(argv[1]);
    if(pHost == NULL){
        fprintf(stderr , "gethostbyname:%s\n", strerror(h_errno));
        return -1;
    }
    printf("host real name = %s\n",pHost->h_name );
    printf("%d\n", pHost->h_addrtype);
    for(int i =0;NULL !=pHost->h_aliases[i] ; i++)
        printf("alias name = %s\n",pHost->h_aliases[i]);
    printf("addrlength = %d\n", pHost->h_length);
    for(int i =0; pHost->h_addr_list[i] != NULL ; i++ ){
        char buf[1024] = {0};
        inet_ntop(pHost->h_addrtype , pHost->h_addr_list[i],buf, sizeof(buf));
        printf("    addr = %s\n", buf);
    }
    
    
    
    
    // printf("%s\n", pHost->h_addr_list[1]); // 域名


}