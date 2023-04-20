#include <stdio.h>
#include <sys/types.h> /* See NOTES */
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    int socket_fd;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0)
    {
        perror("socket");
        return -1;
    }
    struct sockaddr_in ip;
    ip.sin_family = AF_INET;
    ip.sin_port = ntohs(1234);
    ip.sin_addr.s_addr = inet_addr("192.168.145.136");
    if(connect(socket_fd, (struct sockaddr *)&ip, sizeof(ip))<0)
    {
        perror("connect");
        return -1;
    }

    char arr[128];
    int send_val;

    while (1)
    {
        scanf("%s", arr);
        send_val = send(socket_fd, arr, sizeof(arr), 0);
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
    }
    close(socket_fd);
    return 0;
}
