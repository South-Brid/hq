#include <stdio.h>
#include <sys/types.h> /* See NOTES */
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    //1.创建fd
    int socket_fd;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0)
    {
        perror("socket err");
        return -1;
    }
    //2.填充ipv4结构体
    struct sockaddr_in ipv_4;
    ipv_4.sin_family = AF_INET;
    ipv_4.sin_port = htons(1234);
    ipv_4.sin_addr.s_addr = inet_addr("192.168.145.136");
    int bind_val;
    //3.捆绑套接字，ip和端口
    bind_val = bind(socket_fd, (struct sockaddr *)&ipv_4, sizeof(ipv_4));
    if (bind_val < 0)
    {
        perror("bind");
        return -1;
    }
    else
    {
        printf("bind is ok \n");
    }
    //4.监听，转换为被动状态
    int listen_val;
    listen_val = listen(socket_fd, 5); //后面得是监听得端口数
    if (listen_val < 0)
    {
        perror("listen");
        return -1;
    }
    //5.阻塞监听客户端
    int apt;
    apt = accept(socket_fd, NULL, NULL); //不关心是那个客户端就置为空
    if (apt < 0)
    {
        perror("accept");
        return -1;
    }
    char arr[128];
    //6.循环等待客户端消息
    while (1)
    {
        int recv_val;
        recv_val = recv(apt, arr, sizeof(arr), 0);
        if (recv_val < 0)
        {
            perror("recv");
            return -1;
        }
        else if (recv_val == 0)
        {
            printf("client is exit\n");
            break;
        }
        else
        {
            printf("%s\n", arr);
        }
    }
    close(socket_fd);
    close(apt);
    return 0;
}
