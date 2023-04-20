#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        perror("pid");
        return -1;
    }
    else if (pid == 0)
    {
        printf("child : %d %d \n", getpid(), getppid());
        //getpid 获取子进程id
        //getppid 获取父进程id
    }
    else
    {
        printf("parent : %d %d \n", pid, getpid());
    }

    return 0;
}
