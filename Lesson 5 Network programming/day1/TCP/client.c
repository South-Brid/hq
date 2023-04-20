#include <stdio.h>
#include <sys/types.h> /* See NOTES */
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    //1.使用socket创建流式套接子
    int socket_fd;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0)
    {
        perror("socket_fd err");
        return -1;
    }
    //2.请求链接
    struct sockaddr_in cnt;
    cnt.sin_family = AF_INET;
    cnt.sin_port = ntohs(1234);
    cnt.sin_addr.s_addr = inet_addr("192.168.145.136");
    if (connect(socket_fd, (struct sockaddr *)&cnt, sizeof(cnt)) < 0)
    {
        perror("connect err");
        return -1;
    }
    char buf[128];
    int ch;
    while (1)
    {
        ch=read(0,buf,128);
        if (send(socket_fd, buf, ch, 0) < 0)
        {
            perror("send err");
            return -1;
        }
    }
    close(socket_fd);
    return 0;
}
