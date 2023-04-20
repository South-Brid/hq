#include <stdio.h>
#include <sys/types.h> /* See NOTES */
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
//1.向客户端发送文件信息
void ServerList(int apt, char *buf, int sizebuf);
//接受客户端发来得文件
void ServerFilename(int apt, char *buf, int sizebuf);

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("please input : a.out <port_val>\n");
        return -1;
    }
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0)
    {
        perror("socket");
        return -1;
    }
    int port_val = atoi(argv[1]);

    struct sockaddr_in ipv4; //ipv4用来绑定服务器ip和端口 clien_msg用来获取端口消息
    ipv4.sin_family = AF_INET;
    ipv4.sin_port = htons(port_val);
    //ipv4.sin_addr.s_addr = inet_addr(argv[2]);
    //自动获取本机ip地址
    //ipv4.sin_addr.s_addr = inet_addr("0.0.0.0");
    ipv4.sin_addr.s_addr = INADDR_ANY;

    struct sockaddr_in client_msg;
    int len = sizeof(client_msg);

    if (bind(socket_fd, (struct sockaddr *)&ipv4, sizeof(ipv4)) < 0)
    {
        perror("bind");
        return -1;
    }
    if (listen(socket_fd, 5) < 0)
    {
        perror("listen");
        return -1;
    }

    while (1) //用来循环接受客户端
    {
        int apt = accept(socket_fd, (struct sockaddr *)&client_msg, &len);
        if (apt < 0)
        {
            perror("accept");
            return -1;
        }
        printf("client ip:%s  client port:%d \n", inet_ntoa(client_msg.sin_addr), ntohs(client_msg.sin_port));
        char arr[128];
        int ch;
        while (1)
        {
            ch = recv(apt, arr, sizeof(arr), 0); //此处是recv
            if (ch < 0)
            {
                perror("rec");
            }
            else if (ch == 0)
            {
                printf("client is exit");
                break;
            }
            else
            {
                printf("%s", arr); //这里取决与客户端发送得信号
                //1.向客户端发送文件信息
                if (strncmp("list", arr, 4) == 0)
                {
                    ServerList(apt, arr, sizeof(arr));
                }
                //2.接受一个文件
                else if (strncmp("put", arr, 3) == 0)
                {
                    ServerFilename(apt, arr, sizeof(arr));
                }
                //3.传送一个文件
                else if (strncmp("get", arr, 3) == 0)
                {
                    //ServerFilename();
                }
            }
        }
        close(apt); //循环结束就得关闭apt发送和接受得文件描述符
    }
    close(socket_fd);
    return 0;
}
//接受客户端发来得文件
void ServerFilename(int apt, char *buf, int sizebuf)
{
    //1.打开准备好得空白文件
    int fd = open(buf + 4, O_TRUNC | O_CREAT | O_WRONLY, 0666); //客户端和服务器传送得文件名是相同得
    if (fd < 0)
    {
        perror("open fd");
        return;
    }
    //2.接受客户端传来得文件
    while (1)
    {
        if (recv(apt, buf, sizebuf, 0) < 0)
        {
            perror("recv");
            return;
        }
        if (strncmp("PutFilename ok.", buf, 15) == 0)
        {
            break;
        }
        //3.将buf里面得内容写到fd里面
        write(fd, buf, strlen(buf));
    }
}

//1.向客户端发送文件信息
void ServerList(int apt, char *buf, int sizebuf)
{
    //1.打开目录流
    DIR *dir = opendir("./");
    if (dir == NULL)
    {
        perror("opendir");
        return;
    }
    //2.读取文件名
    struct dirent *fn = NULL;
    struct stat st;
    while ((fn = readdir(dir)) != NULL) //循环读取文件
    {
        stat(fn->d_name, &st); //将文件名给结构体
        if (S_ISREG(st.st_mode))
        {
            strcpy(buf, fn->d_name);
            send(apt, buf, sizebuf, 0);
        }
    }
    strcpy(buf, "ok."); //读取完成后得标志
    send(apt, buf, sizebuf, 0);
}
