//初见kill函数
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char const *argv[])
{
    //kill(getpid(), SIGKILL);
    //raise(9);         //给当前进程发送信号
    alarm(5);           //5秒后给程序发送alarm信号
    alarm(1);           //按照最后一次alarm出现得位置为准
    printf("hello world\n");
    pause();             //挂起信号
    return 0;
}
