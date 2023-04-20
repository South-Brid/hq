#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <poll.h>
#include <stdlib.h>
#include <sys/epoll.h>

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
    /*引入epoll函数实现一个服务器有多个客户端链接 */
    //创建epoll_event 结构体来保存文件描述符
    struct epoll_event event;
    struct epoll_event events[20];

    //1>创建tree
    int epfd = epoll_create(1);

    //2>添加关心文件描述符到tree
    event.data.fd = 0;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epfd, EPOLL_CTL_ADD, 0, &event);

    event.data.fd = sockfd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);

    int ret;
    int recvbyte;
    char buf[128];
    while (1)
    {
        //3>epoll_wait等待事件发生
        ret = epoll_wait(epfd, events, 20, -1); //设置为-1表示无限期等待
        if (ret < 0)
        {
            perror("epoll_wait err.");
            return -1;
        }
        for (int i = 0; i < ret; i++)
        {
            if (events[i].data.fd == 0)
            {

                fgets(buf, sizeof(buf), stdin);
                printf("key:%s\n", buf);
            }
            else if (events[i].data.fd == sockfd)
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
                event.data.fd = acceptfd;
                event.events = EPOLLIN | EPOLLET;
                epoll_ctl(epfd, EPOLL_CTL_ADD, acceptfd, &event);
            }
            else
            {
                recvbyte = recv(events[i].data.fd, buf, sizeof(buf), 0);
                if (recvbyte < 0)
                {
                    perror("recv err.");
                    return -1;
                }
                else if (recvbyte == 0)
                {
                    printf("%d client exit.\n", events[i].data.fd);
                    close(events[i].data.fd);
                    epoll_ctl(epfd, EPOLL_CTL_ADD, events[i].data.fd, &event);
                }
                else
                {
                    printf("%d:%s\n", events[i].data.fd, buf);
                }
            }
        }
    }
    close(sockfd);
    return 0;
}
