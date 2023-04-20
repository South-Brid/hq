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
        perror("open err.");
        return -1;
    }
    fd_set readfds, tmpfds;
    FD_ZERO(&readfds);
    FD_SET(0, &readfds);
    FD_SET(fd, &readfds);
    int mutex = fd;
    char buf[32];
    while (1)
    {
        tmpfds = readfds;
        select(mutex + 1, &tmpfds, NULL, NULL, NULL);
        if (FD_ISSET(0, &tmpfds))
        {
            fgets(buf, sizeof(buf), stdin);
            printf("%s\n", buf);
        }
        if (FD_ISSET(fd, &tmpfds))
        {
            read(fd, buf, sizeof(buf));
            printf("%s\n",buf);
        }
    }
    close(fd);
    return 0;
}
