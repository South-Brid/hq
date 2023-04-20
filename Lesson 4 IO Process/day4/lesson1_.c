#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char const *argv[])
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        perror("err");
        return -1;
    }
    else if (pid == 0)
    {
        sleep(1);
        printf("child\n");
    }
    else
    {
        //wait(NULL); //回收子进程状态,要放到父进程当中
        //waitpid(-1,NULL,0);//阻塞函数，等待任意子进程退出
        //waitpid(-1,NULL,WNOHANG);//非阻塞状态，函数立刻返回值
        /*
        waitpid :
        第一个形参：pid
        第二个形参：子进程的退出状态
        第三个形参：参数 0代表阻塞，WNOHANG代表非阻塞
         */
        while (1)
        {
            if (waitpid(-1, NULL, WNOHANG) > 1) //轮寻作用
            {
                break;
            }
        }
        printf("parten\n");
        while (1)
            ;
    }
    return 0;
}
