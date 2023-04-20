/***********广播*********************/
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("please use 3 val\n");
        return -1;
    }

    //广播只能使用数据报套接子
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("sockfd err.");
        return -1;
    }

    struct sockaddr_in saddr, caddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[1]));
    saddr.sin_addr.s_addr = inet_addr("0.0.0.0");

    socklen_t caddr_len = sizeof(caddr);

    bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr));

    char buf[128];
    while (1)
    {
        if (recvfrom(sockfd, buf, sizeof(buf), 0,
                     (struct sockaddr *)&caddr, &caddr_len) < 0)
        {
            perror("recvfrom err.");
            return -1;
        }
        printf("%d %s\n", ntohs(caddr.sin_port), inet_ntoa(caddr.sin_addr));
        printf("%s\n", buf);
    }
    close(sockfd);
    return 0;
}
