#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    //1.创建数据报套接子
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("socket err.");
        return -1;
    }
    //将主机ip加入到多播组
    struct ip_mreq mreq;
     mreq.imr_multiaddr.s_addr=inet_addr(argv[1]);
     mreq.imr_interface.s_addr=inet_addr("0.0.0.0");

    setsockopt(sockfd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq));

    //填充结构体：组播ip和接受方端口
    struct sockaddr_in addr,caddr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_addr.s_addr = inet_addr(argv[1]);

    socklen_t len=sizeof(caddr);

    if(bind(sockfd,(struct sockaddr *)&addr,sizeof(addr))<0)
    {
        perror("bind err.");
        return -1;
    }

    char buf[128];
    while (1)
    {
        recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&caddr,&len);
        printf("ip=%s  port=%d :%s\n",inet_ntoa(caddr.sin_addr),\
        ntohs(caddr.sin_port),buf); 
    }
    close(sockfd);
    return 0;
}
