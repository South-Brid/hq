//司机问题
//思路：先忽略后捕捉
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>

pid_t pid;
void handly(int arg) //父进程
{
    if (arg == SIGUSR1) //信号为SIGUSR1打印
    {
        printf("let's gogogo\n");
    }
    else if (arg == SIGUSR2) //信号为SIGUSR2打印
    {
        printf("stop the bus\n");
    }
    else if (arg == SIGTSTP)
    {
        kill(pid, SIGUSR1); //向售票员发送SIGUSR1
        wait(NULL);//先阻塞
        exit(0);//后推出
    }
}

void handly1(int arg) //子进程
{
    if (arg == SIGINT)
    {
        kill(getppid(), SIGUSR1); //向司机发送SIGUSR1
    }
    else if (arg == SIGQUIT)
    {
        kill(getppid(), SIGUSR2); //向司机发送SIGUSR2
    }
    else if (arg == SIGUSR1) //捕捉SIGUSR1打印
    {
        printf("please get off the bus\n");
        exit(0);
    }
}

int main(int argc, char const *argv[])
{

    pid = fork();
    if (pid < 0)
    {
        perror("error");
        return -1;
    }
    else if (pid == 0) //售票员
    {
        while(1)
        {
        signal(SIGTSTP, SIG_IGN); //忽略stp
        signal(SIGINT, handly1);  //捕捉int
        signal(SIGQUIT, handly1); //捕捉quit 
        signal(SIGUSR1, handly1); //捕捉usr1
        }
    }
    else //司机
    {
        while(1)
        {
        signal(SIGINT, SIG_IGN);  //忽略int
        signal(SIGQUIT, SIG_IGN); //忽略quit
        signal(SIGUSR1, handly);  //捕捉usr1
        signal(SIGUSR2, handly);  //捕捉usr2
        signal(SIGTSTP, handly);  //捕捉stp
        }
    }
    pause();
    return 0;
}
