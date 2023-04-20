#include <stdio.h>
#include <sys/types.h> /* See NOTES */
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("please input : a.out <port_val>\n");
        return -1;
    }
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0)
    {
        perror("socket");
        return -1;
    }

    struct sockaddr_in ipv4; //ipv4用来绑定服务器ip和端口 clien_msg用来获取端口消息
    ipv4.sin_family = AF_INET;
    ipv4.sin_port = htons(atoi(argv[1]));
    //ipv4.sin_addr.s_addr = inet_addr(argv[2]);
    //自动获取本机ip地址
    //ipv4.sin_addr.s_addr = inet_addr("0.0.0.0");
    ipv4.sin_addr.s_addr = INADDR_ANY;

    struct sockaddr_in client_msg;
    int len = sizeof(client_msg);

    if (bind(socket_fd, (struct sockaddr *)&ipv4, sizeof(ipv4)) < 0)
    {
        perror("bind");
        return -1;
    }
    if (listen(socket_fd, 5) < 0)
    {
        perror("listen");
        return -1;
    }

    while (1) //用来循环接受客户端
    {
        pid_t pid;
        pid = fork();
        int apt = accept(socket_fd, (struct sockaddr *)&client_msg, &len);
        if (apt < 0)
        {
            perror("accept");
            return -1;
        }
        printf("client ip:%s  client port:%d \n", inet_ntoa(client_msg.sin_addr), ntohs(client_msg.sin_port));

        if (pid == 0)
        {
            char arr[128];
            int ch;
            while (1)
            {
                ch = recv(apt, arr, sizeof(arr), 0); //此处是recv
                if (ch < 0)
                {
                    perror("rec");
                }
                else if (ch == 0)
                {
                    printf("client is exit\n");
                    break;
                }
                else
                {
                    printf("%s", arr); //这里取决与客户端发送得信号
                }
            }
        }
        close(apt); //循环结束就得关闭apt发送和接受得文件描述符
    }
    close(socket_fd);
    return 0;
}
