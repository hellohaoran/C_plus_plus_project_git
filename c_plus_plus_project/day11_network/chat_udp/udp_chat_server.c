#include <c43func.h>
int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 3);
    int sockFd = socket(AF_INET, SOCK_DGRAM, 0);
    ERROR_CHECK(sockFd, -1, "socket");
    struct sockaddr_in addr;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    socklen_t addrlen = sizeof(addr); 
    bind(sockFd,(struct sockaddr*) &addr,addrlen) ;
    struct sockaddr_in clientaddr;
    socklen_t clientaddr_len = sizeof(clientaddr);
    char buf[1024] = {0};
    recvfrom(sockFd, buf, sizeof(buf), 0, (struct sockaddr *)&clientaddr, &clientaddr_len);
    puts(buf);
    fd_set rdset;

    while (1)
    {
        FD_ZERO(&rdset);
        FD_SET(sockFd, &rdset);
        FD_SET(STDIN_FILENO, &rdset);
        select(sockFd+1, &rdset, NULL, NULL, NULL);
        if (FD_ISSET(sockFd, &rdset))
        {
            bzero(buf, sizeof(buf));
            int ret = recvfrom(sockFd, buf, sizeof(buf), 0, (struct sockaddr *)&addr, &addrlen);
            if (ret == 0)
            {
                // 如果返回值为 0
                puts("chat end!");
                break;
            }
            puts(buf);
        }
        if (FD_ISSET(STDIN_FILENO, &rdset))
        {
            bzero(buf, sizeof(buf));
            int ret_ = read(STDIN_FILENO, buf, sizeof(buf));
            if (ret_ == 0)
            {
                puts("chat end!");
                sendto(sockFd, buf, 0, 0, (struct sockaddr *)&addr, addrlen);
                break;
            }
            sendto(sockFd, buf, strlen(buf), 0, (struct sockaddr *)&addr, addrlen);

        }
    }
    close(sockFd);    
}