//使用进程实现父进程输入，子进程输出
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 30
int main(int argc, char const *argv[])
{
    int fd[2] = {0};
    char arr[N] = "";
    pid_t pid;
    if (pipe(fd) < 0)//用管道
    {
        perror("pipe err");
        return -1;
    }
    pid = fork();
    if (pid < 0)
    {
        perror("err");
        return -1;
    }
    else if (pid == 0)
    {
        while (1)
        {
            read(fd[0], arr, N);
            if (strcmp(arr, "quite")==0)
            {
                break;
            }
            printf("%s\n", arr);
        }
    }
    else
    {
        while (1)
        {
            scanf("%s", arr);
            write(fd[1], arr, strlen(arr) + 1);
            if (strcmp(arr, "quite")==0)
            {
                break;
            }
        }
        wait(NULL);
    }
    return 0;
}
