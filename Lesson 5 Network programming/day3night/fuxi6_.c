//select函数实现io多路复用
//键盘和鼠标
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    int fd = open("/dev/input/mouse0", O_RDONLY);
    if (fd < 0)
    {
        perror("open err");
        return -1;
    }
    fd_set readfdr;
    FD_ZERO(&readfdr);
    FD_SET(0, &readfdr);
    FD_SET(fd, &readfdr);
    char buf;
    int mutex = fd;
    while (1)
    {
        if (select(mutex + 1, &readfdr, NULL, NULL, NULL) < 0)
        {
            perror("select err.");
            return -1;
        }
        if (FD_ISSET(0, &readfdr))
        {
        }
        if (FD_ISSET(fd, &readfdr))
        {
        }
    }
    return 0;
}
