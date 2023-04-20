#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    //1.创建数据报套接子
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("socket err.");
        return -1;
    }

    //设置发送广播权限
    // /************************************************************/
    // int op = 1;
    // setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &op, sizeof(op));
    // /************************************************************/

    //填充结构体：广播ip和接受方端口
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_addr.s_addr = inet_addr(argv[1]);

    char buf[128];
    while (1)
    {
        fgets(buf, sizeof(buf), stdin);
        sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&addr, sizeof(addr));
    }
    close(sockfd);
    return 0;
}
