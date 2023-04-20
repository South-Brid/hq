//信号函数
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    printf("%d\n",alarm(5));
    printf("test\n");
    printf("%d\n",alarm(1));//打印上一个alarm剩余得时间
    //kill(getpid(),SIGINT);
    //raise(SIGINT);
    pause();
    // while(1);
    return 0;
}
