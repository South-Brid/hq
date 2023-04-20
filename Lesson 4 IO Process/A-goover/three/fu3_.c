//关联特性得验证
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char const *argv[])
{
    pid_t pid;
    pid = fork();
    if (pid == -1)
    {
        perror("err");
        return -1;
    }
    else if (pid == 0)
    {
        printf("child \n"); //子进程结束，父进进程未回收资源
        //exit(0);
        while (1)
            ;
    }
    else
    {
        //wait(NULL);//wait函数只能放在进程父进程当中才能回收子进程得资源
        printf("partent \n");
        exit(0);//父进程结束，子进程未结束，子进程会成为孤儿进程
        while (1)
            ;
    }
    return 0;
}
