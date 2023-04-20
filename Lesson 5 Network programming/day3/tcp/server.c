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
#include <dirent.h>

int main(int argc, char const *argv[])
{

    return 0;
}
//接受客户端发送来得文件
void PutFile(int accfd, char *buf, int size) //必须使用size
{
    int fd = open(buf + 4, O_TRUNC | O_CREAT | O_WRONLY, 0666);
    if (fd < 0)
    {
        perror("open");
        return;
    }
    while (1)
    {
        if (recv(accfd, buf, size, 0) < 0)
        {
            perror("recv");
            return;
        }
        if (strncmp("put ok.", buf, 7) == 0)
        {
            break;
        }
        write(fd, buf, strlen(buf));
    }
}
//list发送当前目录信息
void putfile(int accfd, char *buf, int size)
{
    DIR *dir = opendir("./");
    if (dir == NULL)
    {
        perror("opendir");
        return;
    }
    struct stat st;
    struct dirent *rd;
    while ((rd = readdir(dir)) != NULL)
    {
        stat(rd->d_name, &st);
        if (S_ISREG(st.st_mode))
        {
            strcpy(buf, rd->d_name);
            send(accfd, buf, size, 0);
        }
        strcpy(buf, "over");
        send(accfd, buf, size, 0);
    }
}
