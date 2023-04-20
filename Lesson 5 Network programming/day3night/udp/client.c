#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
int main(int argc, char const *argv[])
{
    //1.socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("socket err.");
        return -1;
    }
    //2.ipv4
    struct sockaddr_in caddr;
    caddr.sin_family = AF_INET;
    caddr.sin_port = htons(atoi(argv[1]));
    caddr.sin_addr.s_addr = INADDR_ANY;
    //3.
    char buf[32];
    while (1)
    {
        fgets(buf, sizeof(buf), stdin);
        if (buf[strlen(buf) - 1] == '\n')
        {
            buf[strlen(buf) - 1] == '\0';
        }
        if (sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&caddr, sizeof(caddr)) < 0)
        {
            perror("sendto err.");
            return -1;
        }
    }
    close(sockfd);
    return 0;
}
