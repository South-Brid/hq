/***********组播*********************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("please use 3 val\n");
        return -1;
    }

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("sockfd err.");
        return -1;
    }
    
    struct sockaddr_in caddr;
    caddr.sin_family = AF_INET;
    caddr.sin_port = htons(atoi(argv[1]));
    caddr.sin_addr.s_addr = inet_addr(argv[2]);//组播ip

    char buf[128];
    while (1)
    {
        fgets(buf, sizeof(buf), stdin);
        if (buf[strlen(buf) - 1] == '\n')
        {
            buf[strlen(buf) - 1] = '\0';
        }

        if (sendto(sockfd, buf, sizeof(buf), 0,
                   (struct sockaddr *)&caddr, sizeof(caddr)) < 0)
        {
            perror("recvfrom err.");
            return -1;
        }
    }
    close(sockfd);
    return 0;
}
