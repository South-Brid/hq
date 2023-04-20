#include <stdio.h>
#include <sys/types.h> /* See NOTES */
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

//界面函数
void PrintfJie();
//列出服务器所在目录下的文件名(除目录不显示）
void ClientList(int socket_fd, char *buf, int sizebuf);
//上传一个文件
void PutFilename(int sockfd, char *buf, int sizebuf);

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("please input : a.out <port_val> \n");
        return -1;
    }

    int port_val = atoi(argv[1]);
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0)
    {
        perror("socket");
        return -1;
    }
    struct sockaddr_in ipv4;
    ipv4.sin_family = AF_INET;
    ipv4.sin_port = ntohs(port_val);
    if (connect(socket_fd, (struct sockaddr *)&ipv4, sizeof(ipv4)) < 0)
    {
        perror("bind");
        return -1;
    }

    char arr[128];
    int ch;
    int x;
    while (1)
    {
        PrintfJie();
        fgets(arr, sizeof(arr), stdin); //添加可以增加空格
        if (arr[strlen(arr) - 1] == '\n')
        {
            arr[strlen(arr) - 1] == '\0';
        }
        ch = send(socket_fd, arr, sizeof(arr), 0);
        if (ch < 0)
        {
            perror("rec");
        }
        else if (ch == 0)
        {
            printf("client is exit");
            break;
        }
        //功能处理
        //1.接受服务器传送过来得文件名，打印
        if (strncmp("list", arr, 4) == 0)
        {
            ClientList(socket_fd, arr, sizeof(arr));
        }
        //2.上传一个文件
        else if (strncmp("put", arr, 3) == 0)
        {
            PutFilename(socket_fd, arr, sizeof(arr));
        }
        //3.下载一个文件
        else if (strncmp("get", arr, 3) == 0)
        {
            //GetFilename();
        }
        //4.退出
        else if (strncmp("quite", arr, 5) == 0)
        {
            break;
        }
    }
    close(socket_fd);
    return 0;
}

//上传一个文件
void PutFilename(int sockfd, char *buf, int sizebuf)
{
    //1.打开文件
    int fd = open(buf + 4, O_RDONLY);
    if (fd < 0)
    {
        perror("open fd");
        return;
    }
    int ch;
    while ((ch = read(fd, buf, sizebuf - 1)) != 0) //将fd里面得内容读到buf
    {
        buf[ch] = '\0';
        send(sockfd, buf, sizebuf, 0); //将buf里面得内容发送到服务器
    }
    strcpy(buf, "PutFilename ok."); //结束得标志
    send(sockfd, buf, sizebuf, 0);
}

//界面函数
void PrintfJie()
{
    //1.客户端和服务器链接成功后出现以下提示：四个功能
    printf("***************list**************\n");
    printf("***********put filename**********\n");
    printf("***********get filename**********\n");
    printf("**************quit***************\n");
}
//列出服务器所在目录下的文件名(除目录不显示）
void ClientList(int socket_fd, char *buf, int sizebuf)
{
    while (1)
    {
        if (recv(socket_fd, buf, sizebuf, 0) < 0)
        {
            perror("ClientList recv");
            return;
        }
        if (strncmp("ok.", buf, 3) == 0)
        {
            break;
        }
        printf("%s\n", buf);
    }
}
//PutFilename();
//GetFilename();