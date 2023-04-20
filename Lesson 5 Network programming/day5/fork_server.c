#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>

void handly(int arg)
{
    waitpid(-1, NULL, WNOHANG);
}
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

    //设置端口重复使用
    int optval = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
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
    //4.阻塞等待客户端链接
    while (1)
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
        //循环收发消息
        signal(SIGCHLD, handly);

        pid_t pid;
        pid = fork();
        if (pid < 0)
        {
            perror("fork err.");
            return -1;
        }
        else if (pid == 0)
        {
            char buf[128];
            int ret;
            while (1)
            {
                //setsockopt设置超时检测--给recv设置
                struct timeval tm = {2, 0};
                setsockopt(acceptfd, SOL_SOCKET, SO_RCVTIMEO, &tm, sizeof(tm));
                ret = recv(acceptfd, buf, sizeof(buf), 0);
                if (ret < 0)
                {
                    perror("recv err.");
                    continue;//
                }
                else if (ret == 0)
                {
                    printf("client exit\n");
                    break;
                }
                else
                {
                    printf("buf:%s\n", buf);
                }
            }
            exit(-1); //这里不同
        }
        close(acceptfd); //这里不同
    }
    close(sockfd);
    return 0;
}
