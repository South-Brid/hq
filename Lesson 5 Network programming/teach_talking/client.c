#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#include "head.h"
int main(int argc, char const *argv[])
{
    //创建数据报
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("socket err.");
        return -1;
    }

    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[2]));
    saddr.sin_addr.s_addr = inet_addr(argv[1]);

    //1.登录
    MSG_t msg;
    msg.type = login;
    printf("please input your name:");
    fgets(msg.name, sizeof(msg.name), stdin);
    if (msg.name[strlen(msg.name) - 1] == '\n')
        msg.name[strlen(msg.name) - 1] = '\0';

    sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&saddr, sizeof(saddr));

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork err.");
        return -1;
    }
    else if (pid == 0)
    {
        while (1)
        {
            if (recvfrom(sockfd, &msg, sizeof(msg), 0, NULL, NULL) < 0)
            {
                perror("recvfrom err.");
                return -1;
            }
            printf("%s said %s\n", msg.name, msg.text);
        }
    }
    else
    {
        while (1)
        {
            fgets(msg.text, sizeof(msg.text), stdin);
            if (msg.text[strlen(msg.text) - 1] == '\n')
                msg.text[strlen(msg.text) - 1] = '\0';
            if (strncmp(msg.text, "quit", 4) == 0)
            {
                msg.type = quit;
                sendto(sockfd, &msg, sizeof(msg), 0,
                       (struct sockaddr *)&saddr, sizeof(saddr));
                break;
            }
            else
            {
                msg.type = chat;
            }
            sendto(sockfd, &msg, sizeof(msg), 0,
                   (struct sockaddr *)&saddr, sizeof(saddr));
        }
        kill(pid, SIGKILL);
        wait(NULL);
    }
    close(sockfd);
    return 0;
}
