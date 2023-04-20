#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int fd;

void handler(int sig)
{
    char buf[32];
    int ret = read(fd, buf, sizeof(buf));
    buf[ret] = '\0';
    printf("mouse:%s\n", buf);
}

int main(int argc, char const *argv[])
{
    fd = open("/dev/input/mouse0", O_RDONLY);
    if (fd < 0)
    {
        perror("open err.");
        return -1;
    }
    //1.将fd和进程pid告诉底层驱动
    //作用：当fd有IO操作，底层驱动将SIGIO信号发送给pid
    fcntl(fd, F_SETOWN, getpid());
    
    //设置fd的异步通知属性
    int flags = fcntl(fd, F_GETFL); //1.获取文件描述符原有的属性信息
    flags = flags | O_ASYNC;        //2.修改添加权限
    fcntl(fd, F_SETFL, flags);      //3.将修改好的权限设置回去

    signal(SIGIO, handler);
    while (1)
    {
        sleep(1);
        printf("welcome to hqyj.\n");
    }
    close(fd);
    return 0;
}
