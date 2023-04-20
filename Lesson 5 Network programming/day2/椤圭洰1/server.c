#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//功能：向客户端发送当前路径下得信息
void ServerList(int accpt, char *buf, int val);
//功能：接受服务器发送过来得文件并创建
void ServerFile(int accpt, char *buf, int val);

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

    //优化，服务器显示连接得客户段信息
    struct sockaddr_in seraddr;
    int seraddr_len = sizeof(seraddr);

    //3.绑定
    if (bind(sockfd, (struct sockaddr *)&caddr, sizeof(caddr)) < 0)
    {
        perror("bind");
        return -1;
    }
    //4.监听
    if (listen(sockfd, 5) < 0)
    {
        perror("listen");
        return -1;
    }
    //5.链接客户端
    //优化：当客户端退出得时候服务器不退出，等待接受
    while (1)
    {
        int accpt = accept(sockfd, (struct sockaddr *)&seraddr, &seraddr_len);
        if (accpt < 0)
        {
            perror("accept");
            return -1;
        }
        //优化显示链接得客户端号信息
        printf("端口号：%d\n", ntohs(seraddr.sin_port));
        printf("IP地址：%s\n", inet_ntoa(seraddr.sin_addr));

        //6.发收消息
        char buf[128];
        int ch = 0;
        while (1)
        {
            ch = recv(accpt, buf, sizeof(buf), 0);
            if (ch < 0)
            {
                perror("resv err");
                return -1;
            }
            //优化：客户端退出得时候，服务器出现提示
            else if (ch == 0)
            {
                printf("client exit\n");
                break;
            }
            else
            {
                //功能1：list
                if (strncmp(buf, "list", 4) == 0)
                {
                    ServerList(accpt, buf, sizeof(buf));
                }
                else if (strncmp(buf, "put ", 4) == 0)
                {
                    ServerFile(accpt, buf, sizeof(buf));
                }
            }
        }
        close(accpt);
    }
    close(sockfd);
    return 0;
}
//功能：接受服务器发送过来得文件并创建
void ServerFile(int accpt, char *buf, int val)
{
    //1.打开文件
    int dir = open(buf + 4, O_TRUNC | O_CREAT | O_WRONLY, 0666);
    if (dir < 0)
    {
        perror("open");
        return;
    }
    while (1)
    {
        if(recv(accpt, buf, val, 0)<0)
        {
            perror("recv err.");
            return;
        }
        if (strncmp(buf, "put ok.", 7) == 0)
        {
            break;
        }
        write(dir, buf, strlen(buf)); //此处
    }
}

//功能：向客户端发送当前路径下得信息
void ServerList(int accpt, char *buf, int val)
{
    //1.打开当前路径

    DIR *dir = opendir("./");
    if (dir == NULL)
    {
        perror("open dir");
        return;
    }
    struct dirent *serlist;
    struct stat st;
    while ((serlist = readdir(dir)) != NULL) //循环读取文件
    {
        stat(serlist->d_name, &st);
        if (S_ISREG(st.st_mode))
        {
            strcpy(buf, serlist->d_name); //将文件得名字拷贝到buf里面
            send(accpt, buf, val, 0);
        }
    }
    strcpy(buf, "fist ok."); //将结束标志拷贝到buf里面
    send(accpt, buf, val, 0);
}