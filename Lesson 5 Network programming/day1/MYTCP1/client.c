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
    //创建套接字
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0)
    {
        perror("socket\n");
        return -1;
    }
    struct sockaddr_in ipv_4;
    ipv_4.sin_family = AF_INET;
    ipv_4.sin_port = ntohs(1234);
    ipv_4.sin_addr.s_addr = inet_addr("192.168.145.136");
    int con;
    //请求链接，也需要套接字，ip和端口
    con = connect(socket_fd, (struct sockaddr *)&ipv_4, sizeof(ipv_4));
    if (con < 0)
    {
        perror("connect");
        return -1;
    }
    //向服务器发送信息
    char arr[128];
    while (1)
    {
        scanf("%s",arr);
        int send_val = send(socket_fd, arr, sizeof(arr), 0);
        if (send_val < 0)
        {
            perror("send");
            return -1;
        }
        else if (send_val == 0)
        {
            printf("server is exit");
            break;
        }
        if (strncmp(arr, "quite", 5) == 0)
        {
            break;
        }
    }
    close(socket_fd);
    return 0;
}
