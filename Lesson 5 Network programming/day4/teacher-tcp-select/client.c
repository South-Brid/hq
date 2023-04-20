#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void show(void);
void list_client(int sockfd, char *buf, int size);
void put_client(int sockfd, char *buf, int size);
void get_client(int sockfd, char *buf, int size);
int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("please input %s <ip> <port>\n", argv[0]);
        return -1;
    }
    //1.创建套接子
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("socket err.");
        return -1;
    }

    //填充结构体
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[2]));
    saddr.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    {
        perror("connect err.");
        return -1;
    }
    //收发消息
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork err");
        return -1;
    }
    else if (pid == 0)
    {
        char buf[128];
        while (1)
        {
            fgets(buf, sizeof(buf), stdin);
            if (buf[strlen(buf) - 1] == '\n')
            {
                buf[strlen(buf) - 1] == '\0';
            }
            send(sockfd, buf, sizeof(buf), 0);
        }
    }
    else
    {
        char buf[128];
        int recvtype;
        while (1)
        {
            recvtype = recv(sockfd, buf, sizeof(buf), 0);
            if (recvtype < 0)
            {
                perror("recv err");
                return -1;
            }
            printf("%s\n", buf);
        }
    }
    close(sockfd);
    return 0;
}