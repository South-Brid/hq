#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char const *argv[])
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0); //创建数据包套接字
    if (sockfd < 0)
    {
        perror("socket err");
        return -1;
    }
    struct sockaddr_in saddr, caddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[1]));
    saddr.sin_addr.s_addr = INADDR_ANY;

    socklen_t len = sizeof(caddr);

    if (bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    {
        perror("bind err");
        return -1;
    }
    char buf[128];
    while (1)
    {
        if (recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&caddr, &len) < 0)
        {
            perror("recvfrom err");
            return -1;
        }
        printf("端口号：%d\n",ntohs(caddr.sin_port));
        printf("ip：%s\n",inet_ntoa(caddr.sin_addr));
        printf("%s",buf);
    }
    return 0;
}
