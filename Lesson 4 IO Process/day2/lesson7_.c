#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
int main(int argc, char const *argv[])
{
    int fd;//定义一个文件描述符
    fd = open("7.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("7.txt err");
        return -1;
    }
    printf("%d", fd);
    return 0;
}
