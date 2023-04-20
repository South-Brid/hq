//poll改为epoll
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
#include <signal.h>
#include <poll.h>
#include <sys/epoll.h>

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("use:fd\n");
        return -1;
    }
    //1.socket
    int socked = socket(AF_INET, SOCK_STREAM, 0);
    if (socked < 0)
    {
        perror("socket err.");
        return -1;
    }
    //2.listen_fd
    struct sockaddr_in listen_addr, accept_addr;
    listen_addr.sin_family = AF_INET;
    listen_addr.sin_port = htons(atoi(argv[1]));
    listen_addr.sin_addr.s_addr = INADDR_ANY;

    socklen_t len = sizeof(accept_addr);

    //3.bind
    if (bind(socked, (struct sockaddr *)&listen_addr, sizeof(listen_addr)) < 0)
    {
        perror("bind err.");
        return -1;
    }
    //4.listen
    listen(socked, 10);

    struct epoll_event event;       //创建存放文件描述符号
    struct epoll_event events[100]; //老师说得小车
    //1>创建tree
    int tree = epoll_create(1);

    //2.添加关心得文件描述符
    event.data.fd = 0;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(tree, EPOLL_CTL_ADD, 0, &event);

    event.data.fd = socked;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(tree, EPOLL_CTL_ADD, socked, &event);

    int recv_num;
    int accept_num;
    char buf[128];
    int ret;

    //存在疑惑
    while (1)
    {
        //3.调用epoll_wait
        ret = epoll_wait(tree, events, 100, -1);
        if (ret < 0)
        {
            perror("epoll_wait");
            return -1;
        }
        for (int i = 0; i < ret; i++) //不是等与
        {
            if (events[i].data.fd == 0)
            {
                fgets(buf, sizeof(buf), stdin);
                printf("key:%s", buf);//????????这里打印乱码
                // send(pds[i].fd, buf, sizeof(buf), 0);这里发不过去
            }
            else if (events[i].data.fd == socked)
            {
                accept_num = accept(socked, (struct sockaddr *)&accept_addr, &len);
                if (accept_num < 0)
                {
                    perror("accept err.");
                    return -1;
                }
                printf("duan:%d ip:%s talk:%s \n",
                       ntohs(accept_addr.sin_port), inet_ntoa(accept_addr.sin_addr),
                       buf);
                event.data.fd = accept_num;
                event.events = EPOLLIN | EPOLLET;
                epoll_ctl(tree, EPOLL_CTL_ADD, accept_num, &event);
            }
            else
            {
                recv_num = recv(events[i].data.fd, buf, sizeof(buf), 0);
                if (recv_num < 0)
                {
                    perror("recv err.");
                    return -1;
                }
                else if (recv_num == 0) //三个都是这里出现问题
                {
                    printf("client is exit\n");
                    epoll_ctl(tree, EPOLL_CTL_DEL, events[i].data.fd, NULL); //这里出现问题
                }
                else
                {
                    printf("%d client:%s\n", events[i].data.fd, buf);
                }
            }
        }
    }
    close(socked);
    return 0;
}
