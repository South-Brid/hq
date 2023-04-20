//select函数实现io多路复用
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
    //打开鼠标
    int fd = open("/dev/input/mouse0", O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return -1;
    }
    //1.创建表
    fd_set readfds;
    FD_ZERO(&readfds); //清空表
    //2.将关心得文件描述符添加到表中
    FD_SET(0, &readfds);
    FD_SET(fd, &readfds);
    int fd_time = fd;
    int ret; //错误检测
    char buf[32];

    fd_set tmpfds;

    //注释代码只能检测一次，使用新思路
    // while (1)
    // {
    //     //3.循环调用函数检测select
    //     ret = select(fd_time + 1, &readfds, NULL, NULL, NULL);
    //     if (ret < 0)
    //     {
    //         perror("selsect err.");
    //         return -1;
    //     }
    //     //4.使用宏函数FD_ISSET检测表
    //     if (FD_ISSET(0, &readfds))
    //     {
    //         //键盘
    //         fgets(buf, 32, stdin);
    //         printf("key:%s\n", buf);
    //     }
    //     if (FD_ISSET(fd, &readfds))
    //     {
    //         int ch = read(fd, buf, sizeof(buf));
    //         buf[ch] = '\0';
    //         printf("mouse:%s\n", buf);
    //     }
    //     //鼠标
    // }
       while (1)
    {
        //3.循环调用函数检测select
        tmpfds=readfds;
        ret = select(fd_time + 1, &tmpfds, NULL, NULL, NULL);
        if (ret < 0)
        {
            perror("selsect err.");
            return -1;
        }
        //4.使用宏函数FD_ISSET检测表
        if (FD_ISSET(0, &tmpfds))
        {
            //键盘
            fgets(buf, 32, stdin);
            printf("key:%s\n", buf);
        }
        if (FD_ISSET(fd, &tmpfds))
        {
            int ch = read(fd, buf, sizeof(buf));
            buf[ch] = '\0';
            printf("mouse:%s\n", buf);
        }
        //鼠标
    }
    close(fd);
    return 0;
}
