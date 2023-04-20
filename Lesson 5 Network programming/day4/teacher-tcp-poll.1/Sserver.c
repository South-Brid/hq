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
#include <poll.h>

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
    /*引入poll函数实现一个服务器有多个客户端链接 */
    //1>创建pollfd结构体数组
    struct pollfd fds[100] = {};
    //2>添加关心文件描述符
    fds[0].fd = 0;
    fds[0].events = POLLIN; //读事件
    //event 等待的事件掩码
    fds[1].fd = sockfd;
    fds[1].events = POLLIN; //读事件

    int last = 1; //保存数组中最后一个有效元素的下标

    int ret;
    int recvbyte;
    char buf[128];
    while (1)
    {
        //3>调用poll检测
        ret = poll(fds, last + 1, -1); //设置为-1表示无限期等待
        if (ret < 0)
        {
            perror("poll is err.");
            return -1;
        }
        //4>poll返回，将产生事件的文件描述符的第二个结构体成员值赋值第三个
        //将events下面得宏返回给revents
        //若是没有产生事件revents为0
        for (int i = 0; i <= last; i++)
        {
            if (fds[i].revents == POLLIN)
            {
                if (fds[i].fd == 0)
                {
                    fgets(buf, sizeof(buf), stdin);
                    printf("key:%s\n", buf);
                }
                else if (fds[i].fd == sockfd)
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
                    last++;
                    fds[last].fd = acceptfd;
                    fds[last].events = POLLIN;
                }
                else
                {
                    recvbyte = recv(fds[i].fd, buf, sizeof(buf), 0);
                    if (recvbyte < 0)
                    {
                        perror("recv err.");
                        return -1;
                    }
                    else if (recvbyte == 0)
                    {
                        printf("%d client exit.\n", fds[i].fd);
                        close(fds[i].fd);
                        fds[i] = fds[last];
                        i--;
                        last--;
                    }
                    else
                    {
                        printf("%d:%s\n", fds[i].fd, buf);
                    }
                }
            }
        }
    }

    close(sockfd);
    return 0;
}
