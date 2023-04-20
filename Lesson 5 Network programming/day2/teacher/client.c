#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void show(void);
void list_client(int sockfd, char *buf, int size);
void put_client(int sockfd, char *buf, int size);
void get_client(int sockfd, char *buf, int size);
int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("please input %s <ip> <port>\n", argv[0]);
        return -1;
    }
    //1.创建套接子
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("socket err.");
        return -1;
    }

    //填充结构体
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(atoi(argv[2]));
    saddr.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    {
        perror("connect err.");
        return -1;
    }
    //收发消息
    char buf[128];
    while (1)
    {
        //1.请求窗口
        show();
        //2.获取请求
        fgets(buf, sizeof(buf), stdin);
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = '\0';
        send(sockfd, buf, sizeof(buf), 0);
        if (strncmp(buf, "list", 4) == 0)
        { //循环接收服务器发送过来的普通文件名输出到终端
            list_client(sockfd, buf, sizeof(buf));
        }
        else if (strncmp(buf, "put ", 4) == 0)
        { //上传文件(本地：打开文件读内容发送给服务器)
            put_client(sockfd,buf,sizeof(buf));
        }
        else if (strncmp(buf, "get ", 4) == 0)
        { //下载服务器路径下的文件
            //(本地：打开新建文件接收服务器发送过来的内容写到文件)
            get_client(sockfd,buf,sizeof(buf));
        }
        else if (strncmp(buf, "quit", 4) == 0)
        {
            break;
        }
    }
    close(sockfd);
    return 0;
}
//3.get
void get_client(int sockfd, char *buf, int size)
{
    int fd = open(buf + 4, O_TRUNC | O_CREAT | O_WRONLY, 0666);
    if (fd < 0)
    {
        perror("open err.");
        return;
    }
    while (1)
    {
        if (recv(sockfd, buf, size, 0) < 0)
        {
            perror("recv err.");
            return;
        }
        if (strncmp(buf, "get ok.", 7) == 0)
            break;
        write(fd, buf, strlen(buf));
    }
}
//2.put 上传文件(本地：打开文件读内容发送给服务器)
void put_client(int sockfd, char *buf, int size) //buf->put xxx.c
{
    //1>打开文件 读
    int fd = open(buf + 4, O_RDONLY);
    if (fd < 0)
    {
        perror("open file err.");
        return;
    }
    int ret; //实际读到的个数
    while ((ret = read(fd, buf, size - 1)) != 0)
    {
        buf[ret] = '\0';
        send(sockfd, buf, size, 0);
    }
    strcpy(buf, "put ok.");
    send(sockfd, buf, size, 0);
}

//1.list:循环接收服务器发送过来的普通文件名输出到终端
void list_client(int sockfd, char *buf, int size)
{

    while (1)
    {
        if (recv(sockfd, buf, size, 0) < 0)
        {
            perror("list recv err.");
            return;
        }
        if (strncmp(buf, "list ok.", 8) == 0)
        {
            break;
        }
        printf("%s\n", buf);
    }
}

void show(void)
{
    printf("************list***************\n");
    printf("************put filename*******\n");
    printf("************get filename*******\n");
    printf("************quit***************\n");
}
