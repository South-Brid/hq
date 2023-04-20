#include <stdio.h>
#include <sys/types.h> /* See NOTES */
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <sys/types.h> /* See NOTES */
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int socket_fd;
    socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socket_fd < 0)
    {
        perror("socket_fd err");
        return -1;
    }
    //2.请求链接
    struct sockaddr_un cnt;
    bzero(&cnt, sizeof(cnt));
    cnt.sun_family = AF_UNIX;
    strcpy(cnt.sun_path, "./mutex");

    if (connect(socket_fd, (struct sockaddr *)&cnt, sizeof(cnt)) < 0)
    {
        perror("connect err");
        return -1;
    }
    char buf[128];
    int ch;
    while (1)
    {
        ch = read(0, buf, 128);
        if (send(socket_fd, buf, ch, 0) < 0)
        {
            perror("send err");
            return -1;
        }
    }
    close(socket_fd);
    return 0;
}
