#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, char const *argv[])
{

    return 0;
}
//发送文件夹
void GetFile(int sockfd, char *buf, int size) //必须使用size
{
    int fd = open(buf + 4, O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return;
    }
    int ch;
    while ((ch = read(fd, buf, size - 1)) != 0)
    {
        buf[ch] = '\0';
        send(sockfd, buf, size, 0);
    }
    strcpy(buf, "put ok.");
    send(sockfd, buf, size, 0);
}
//list发送文件
void getlist(int sockfd, char* buf, int size)
{
    if (recv(sockfd, buf, size, 0) < 0)
    {
        perror("recv");
        return;
    }
    while (1)
    {
        if (strncmp("over", buf, 4) == 0)
        {
            break;
        }
        else
        {
            printf("%s\n", buf);
        }
    }
}