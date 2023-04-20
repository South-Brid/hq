#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>

/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    //打开鼠标
    int fd = open("/dev/input/mouse0", O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return -1;
    }
    char buf[32];
    //创建表
    fd_set readfds, tmpfds;
    //清空表
    FD_ZERO(&readfds);
    //表加符
    FD_SET(0, &readfds);
    FD_SET(fd, &readfds);
    int fd_stop = fd;
    int ret;
    while (1)
    {
        tmpfds = readfds;
        ret = select(fd_stop + 1, &tmpfds, NULL, NULL, NULL);
        if (ret < 0)
        {
            perror("select err.");
            return -1;
        }
        if (FD_ISSET(0, &tmpfds))
        {
            //键盘
            fgets(buf, 32, stdin);
            printf("key:%s\n", buf);
        }
        if (FD_ISSET(fd, &tmpfds))
        {
            //鼠标
            int ch = read(fd, buf, sizeof(buf));
            buf[ch] = '\0';
            printf("mouse:%s\n", buf);
        }
    }
    close(fd);
    return 0;
}
