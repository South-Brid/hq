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
    //1>create fd_fet
    fd_set readfds, tempfds;
    FD_ZERO(&readfds);
    FD_SET(0, &readfds);
    FD_SET(socked, &readfds);

    int max_fd = socked;
    int recv_num;
    int accept_num;
    char buf[128];
    while (1)
    {
        tempfds = readfds;
        int ret = select(max_fd + 1, &tempfds, NULL, NULL, NULL);
        if (ret < 0)
        {
            perror("select err.");
            return -1;
        }
        if (FD_ISSET(0, &tempfds))
        {
            fgets(buf, sizeof(buf), stdin);
            printf("key:%s\n", buf);
            for (int i = 4; i <= max_fd; i++)
            {
                if (FD_ISSET(i, &readfds))
                {
                    send(i, buf, sizeof(buf), 0);
                }
            }
        }
        if (FD_ISSET(socked, &tempfds))
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

            FD_SET(accept_num, &readfds);
            if (max_fd < accept_num)
            {
                max_fd = accept_num;
            }
        }

        /************不熟悉**************/
        for (int i = 4; i <= max_fd; i++) //for循环出现问题
        {
            if (FD_ISSET(i, &tempfds))
            {
                recv_num = recv(i, buf, sizeof(buf), 0);
                if (recv_num < 0)
                {
                    perror("recv err.");
                    return -1;
                }
                else if (recv_num == 0)
                {
                    printf("client is exit\n");
                    close(i);
                    FD_CLR(i, &readfds);

                    if (i == max_fd)
                    {
                        max_fd--;
                    }

                    break;
                }
                else
                {
                    printf("%d client:%s\n", i, buf);
                }
            }
        }
        // close(accept_fd);这里无关闭
    }
    close(socked);
    return 0;
}
