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

//功能1：界面提示
void PrintfShow();
//功能2：list
void ClientList(int sockfd, char *buf, int val);
//功能3：put filename
void Putfile(int sockfd, char *buf, int val);

int main(int argc, char const *argv[])
{
    //1.创建套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        perror("sockfd");
        return -1;
    }
    //2.填充结构体
    struct sockaddr_in caddr;
    caddr.sin_family = AF_INET;
    caddr.sin_port = htons(atoi(argv[1]));
    caddr.sin_addr.s_addr = INADDR_ANY;
    //3.链接服务器
    if (connect(sockfd, (struct sockaddr *)&caddr, sizeof(caddr)) < 0)
    {
        perror("connect");
        return -1;
    }
    //4.发送消息
    char buf[128];
    int ch;
    while (1)
    {
        PrintfShow();
        fgets(buf, 128, stdin);
        //优化：去掉\n
        if (buf[strlen(buf) - 1] == '\n')
        {
            buf[strlen(buf) - 1] == '\0';
        }
        ch = send(sockfd, buf, sizeof(buf), 0);
        if (ch < 0)
        {
            perror("send");
            return -1;
        }

        //功能添加
        if (strncmp(buf, "list", 4) == 0)
        {
            ClientList(sockfd, buf, sizeof(buf));
        }
        else if (strncmp(buf, "put ", 4) == 0) //注意点
        {
            Putfile(sockfd, buf, sizeof(buf));
        }
    }
    close(sockfd);
    return 0;
}
//功能3：put filename
void Putfile(int sockfd, char *buf, int val)
{
    //1.打开文件要发送得文件
    int fd = open(buf + 4, O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return;
    }
    //2.将文件里内容读出来
    int ch;
    while ((ch = read(fd, buf, val - 1)) != 0) //此处
    {                                          //3.发送给服务器
        buf[ch] = '\0';
        send(sockfd, buf, val, 0);
    }
    strcpy(buf, "put ok.");
    send(sockfd, buf, val, 0);
}

//功能2：list
void ClientList(int sockfd, char *buf, int val)
{
    //1.接受服务器传回来得内容
    while (1)
    {
        if (recv((sockfd), buf, val, 0) < 0)
        {
            perror("ClientList");
            return;
        }
        else
        {
            if (strncmp(buf, "fist ok.", 8) == 0)
            {
                break;
            }
            else
            {
                printf("%s\n", buf);
            }
        }
    }
}

//功能1：界面提示
void PrintfShow()
{
    printf("***************list**************\n");
    printf("***********put filename**********\n");
    printf("***********get filename**********\n");
    printf("**************quit***************\n");
}