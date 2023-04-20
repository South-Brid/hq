#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>
/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("please input %s <port>\n", argv[0]);
        return -1;
    }
    //1.创建流式套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); //链接
    if (sockfd < 0)
    {
        perror("socket err.");
        return -1;
    }
    printf("sockfd:%d\n", sockfd); //3
    //填充ipv4的通信结构体

    struct sockaddr_in saddr, caddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[1])); 
    saddr.sin_addr.s_addr = inet_addr("0.0.0.0");

    socklen_t len = sizeof(caddr);

    //2.绑定套接字 ip和端口(自己)
    if (bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    {
        perror("bind err.");
        return -1;
    }
    printf("bind ok.\n");

    //3.监听
    if (listen(sockfd, 5) < 0)
    {
        perror("listen err.");
        return -1;
    }
    printf("listen ok.\n");
    /*引入select实现一个服务器有多个客户端链接 */
    //1>创建表
    fd_set readfds, tempfds;
    FD_ZERO(&readfds);
    //2》添加关心文件描述符
    FD_SET(0, &readfds);
    FD_SET(sockfd, &readfds);
    int maxfd = sockfd; //3

    int ret;
    int recvbyte;
    char buf[128];
    while (1)
    {
        tempfds = readfds;
        //3>调用select检测
        ret = select(maxfd + 1, &tempfds, NULL, NULL, NULL);
        if (ret < 0)
        {
            perror("select err.");
            return -1;
        }
        if (FD_ISSET(0, &tempfds))
        {
            //键盘
            fgets(buf, sizeof(buf), stdin);
            printf("key:%s\n", buf);
            for (int i = 4; i <= maxfd; i++)
            {
                if (FD_ISSET(i, &readfds))
                {
                    send(i, buf, sizeof(buf), 0);
                }
            }
        }
        if (FD_ISSET(sockfd, &tempfds))
        {
            int acceptfd = accept(sockfd, (struct sockaddr *)&caddr, &len);
            if (acceptfd < 0)
            {
                perror("accept err.");
                return -1;
            }
            printf("acceptfd=%d\n", acceptfd); //通信
            printf("client:ip=%s port=%d\n",
                   inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));
            FD_SET(acceptfd, &readfds);
            if (maxfd < acceptfd)
                maxfd = acceptfd;
        }
        for (int i = 4; i <= maxfd; i++)
        {
            if (FD_ISSET(i, &tempfds))
            {
                recvbyte = recv(i, buf, sizeof(buf), 0);
                if (recvbyte < 0)
                {
                    perror("recv err.");
                    return -1;
                }
                else if (recvbyte == 0)
                {
                    printf("%d client exit.\n", i);
                    close(i);
                    FD_CLR(i, &readfds);
                    if (i == maxfd)
                        maxfd--;
                }
                else
                {
                    printf("%d:%s\n", i, buf);
                }
            }
        }
    }
    close(sockfd);
    return 0;
}
