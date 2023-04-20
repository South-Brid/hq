#include <stdio.h>
#include <sys/types.h> /* See NOTES */
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("please input : a.out <port_val> \n");
        return -1;
    }

    int port_val = atoi(argv[1]);
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0)
    {
        perror("socket");
        return -1;
    }
    struct sockaddr_in ipv4;
    ipv4.sin_family = AF_INET;
    ipv4.sin_port = ntohs(port_val);
    //ipv4.sin_addr.s_addr = inet_addr(argv[2]);
    //自动获取本机ip地址
    //ipv4.sin_addr.s_addr = inet_addr("0.0.0.0");
    //ipv4.sin_addr.s_addr = INADDR_ANY;
    if (connect(socket_fd, (struct sockaddr *)&ipv4, sizeof(ipv4)) < 0)
    {
        perror("bind");
        return -1;
    }
    char arr[128];
    int ch;
    int x;
    while (1)
    {
        fgets(arr, 128, stdin); //添加可以增加空格
        /**********************************************/
        //去掉fgets获取的多余的'\n'
        if (arr[strlen(arr) - 1] == '\n')
        {
            arr[strlen(arr) - 1] == '\0';
        }
        /**********************************************/
        ch = send(socket_fd, arr, sizeof(arr), 0);
        if (ch < 0)
        {
            perror("rec");
        }
        else if (ch == 0)
        {
            printf("client is exit");
            break;
        }
    }
    close(socket_fd);
    return 0;
}
