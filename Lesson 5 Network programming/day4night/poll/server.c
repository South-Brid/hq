//select改为poll
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

    //1>create

    struct pollfd pds[100] = {};
    //2>添加关心得文件描述符注意这里
    pds[0].fd = 0;
    pds[0].events = POLLIN;

    pds[1].fd = socked;
    pds[1].events = POLLIN;

    int last = 1; //记录最大下标
    int recv_num;
    int accept_num;
    char buf[128];

    while (1)
    {

        if (poll(pds, last + 1, -1) < 0)
        {
            perror("poll err.");
            return -1;
        }
        for (int i = 0; i <= last; i++)
        {
            if (pds[i].revents == POLLIN) //这里
            {
                if (pds[i].fd == 0) //这里自己逻辑错误
                {
                    fgets(buf, sizeof(buf), stdin);
                    printf("key:%s\n", buf);
                   // send(pds[i].fd, buf, sizeof(buf), 0);这里发不过去
                }
                else if (pds[i].fd == socked)
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
                    /******存在疑惑******/
                    last++;
                    pds[i].fd = accept_num;
                    pds[i].events = POLLIN;
                }
                else
                {
                    recv_num = recv(pds[i].fd, buf, sizeof(buf), 0);
                    if (recv_num < 0)
                    {
                        perror("recv err.");
                        return -1;
                    }
                    else if (recv_num == 0)
                    {
                        printf("client is exit\n");
                        close(pds[i].fd); //这里出现问题
                        pds[i] = pds[last];
                        i--;
                        last--;
                    }
                    else
                    {
                        printf("%d client:%s\n", pds[i].fd, buf);
                    }
                }
            }
        }
    }
    close(socked);
    return 0;
}
