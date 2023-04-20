//创建进程
#include <stdio.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    pid_t pid;
    pid = fork();
    if (pid == -1)
    {
        perror("err");
        return -1;
    }
    else if (pid == 0)//子进程
    {
        printf("child \n");
        while (1)
            ;
    }
    else//父进程
    {
        printf("partent \n");
        while (1)
            ;
    }
    return 0;
}
