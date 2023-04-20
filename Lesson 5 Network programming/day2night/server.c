#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, char const *argv[])
{
    char buf[128] = "";

    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        perror("socket");
        return -1;
    }
    struct sockaddr_in saddr, recvddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[1]));
    saddr.sin_addr.s_addr = INADDR_ANY;

    socklen_t len = sizeof(recvddr);

    if (bind(socketfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    {
        perror("bind");
        return -1;
    }
    while (1)
    {
        int recvid = recvfrom(socketfd, buf, sizeof(buf),
         0, (struct sockaddr *)&recvddr, &len);
        if (recvid < 0)
        {
            perror("recvfrom");
            return -1;
        }
        else if (recvid == 0)
        {
            printf("client is exit\n");
            break;
        }else
        {
            printf("%s\n",buf);
        }
    }
    close(socketfd);
    return 0;
}
