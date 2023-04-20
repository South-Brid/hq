#include <stdio.h>
#include <sys/types.h> /* See NOTES */
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0)
    {
        perror("socket");
        return -1;
    }
    struct sockaddr_in ipv_4;
    ipv_4.sin_family = AF_INET;
    ipv_4.sin_port = htons(1234);
    ipv_4.sin_addr.s_addr = inet_addr("192.168.145.136");
    if (bind(socket_fd, (struct sockaddr *)&ipv_4, sizeof(ipv_4)) < 0)
    {
        perror("bind");
        return -1;
    }
    if (listen(socket_fd, 5) < 0)
    {
        perror("listen");
        return -1;
    }
    int act = accept(socket_fd, NULL, NULL);
    if (act < 0)
    {
        perror("accept");
        return -1;
    }
    char arr[128];
    int ch;
    while (1)
    {
        ch = recv(act, arr, sizeof(arr), 0);
        if (ch < 0)
        {
            perror("recv");
            return -1;
        }
        else if (ch == 0)
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
    close(act);
    return 0;
}
