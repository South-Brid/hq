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
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[1]));
    saddr.sin_addr.s_addr = inet_addr(argv[2]);
    socklen_t len = sizeof(saddr);
    char buf[128];
    while (1)
    {
        fgets(buf, sizeof(buf), stdin);
        if (buf[strlen(buf) - 1] == '\n')
        {
            buf[strlen(buf) - 1] == '\0';
        }
        if (sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&saddr, len) < 0)
        {
            perror("recvfrom err");
            return -1;
        }
    }
    return 0;
}
