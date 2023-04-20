/***********??­*********************/
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
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

    //?????
    struct ip_mreq mreq;
    bzero(&mreq, sizeof(mreq));
    mreq.imr_multiaddr.s_addr = inet_addr(argv[2]); //??ip
    mreq.imr_interface.s_addr = INADDR_ANY;
    setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
    //224.0.0.1 – 239.255.255.255

    struct sockaddr_in saddr, caddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[1]));//??
    // saddr.sin_addr.s_addr = inet_addr("0.0.0.0");
    saddr.sin_addr.s_addr = inet_addr(argv[2]);

    socklen_t caddr_len = sizeof(caddr);

    bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr));

    char buf[128];
    while (1)
    {
        if (recvfrom(sockfd, buf, sizeof(buf), 0,
                     (struct sockaddr *)&caddr, &caddr_len) < 0)
        {
            perror("recvfrom err.");
            return -1;
        }
        printf("%d %s\n", ntohs(caddr.sin_port), inet_ntoa(caddr.sin_addr));
        printf("%s\n", buf);
    }
    close(sockfd);
    return 0;
}
