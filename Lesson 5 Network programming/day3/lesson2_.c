//信号驱动IO
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int fd;
void handly(int sig)
{
    char buf[32];
    int ret = read(fd, buf, 32);
    buf[ret] = '\0';
    printf("mouse:%s\n", buf);
}
int main(int argc, char const *argv[])
{

    fd = open("/dev/input/mouse0", O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return -1;
    }
    //1.将fd和进程pid告诉底层驱动
    //作用：当fd有IO操作，底层驱动将SIGIO信号发送给pid
    fcntl(fd, F_SETOWN, getpid());//
    //2.设置fd添加哦——async属性
    int flags = fcntl(fd, F_GETFL);
    flags = flags | O_ASYNC; //添加异步权限
    fcntl(fd, F_SETFL, flags);
    
    signal(SIGIO, handly);
    while (1)
    {
        sleep(1);
        printf("hello world\n");
    }
    close(fd);
    return 0;
}
