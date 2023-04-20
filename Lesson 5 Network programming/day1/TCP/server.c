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

    //socket第一个参数已经是AF_INET ipv4,是用bind函数得填充ipv4结构体
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[1]));                         //端口占了两个字节,将小端转换为大端
    saddr.sin_addr.s_addr = inet_addr("192.168.145.136"); //从人看的ip地址转为机器使用的32位无符号整数
    //2.绑定套接字，ip和端口
    if (bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    {
        perror("bind");
        return -1;
    }
    else
    {
        printf("bind ok\n");
    }
    //3.监听-被动状态
    if (listen(sockfd, 5) < 0)
    {
        perror("listen err");
        return -1;
    }
    //4.阻塞等待客户端链接
    int accept_fd = accept(sockfd, NULL, NULL);
    if (accept_fd < 0)
    {
        perror("accept err");
        return -1;
    }
    //5.循环接受消息
    char arr[128];
    ssize_t ret;
    while (1)
    {
        ret = recv(accept_fd, arr, sizeof(arr), 0);//这里注意下
        if (ret < 0)
        {
            perror("recv err");
            return -1;
        }
        else if (ret == 0)
        {
            perror("clien exit");
            break;
        }
        else
        {
            write(1,arr,ret);
        }
    }
    close(sockfd);
    close(accept_fd);
    return 0;
}
