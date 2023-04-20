#include <stdio.h>
#include <sys/types.h> /* See NOTES */
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include<unistd.h>

int main(int argc, char const *argv[])
{
    //1.使用socket函数-创建流式套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("scoket err");
        return -1;
    }

    //填充服务端地址结构体
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(8888);
    saddr.sin_addr.s_addr = inet_addr("192.168.145.136");

    //2.连接服务端
    if (connect(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    {
        perror("connect err");
        return -1;
    }
    else
    {
        printf("connect ok\n");
    }

    //3.循环发送消息
    char arr[128];
    int ret;
    while (1)
    {
        printf("Please enter message: ");
        fgets(arr, sizeof(arr), stdin);
        ret = send(sockfd, arr, sizeof(arr), 0);
        if (ret < 0)
        {
            perror("send err");
            return -1;
        }
    }

    close(sockfd);
    return 0;
}
