//使用无名管道完成以前得操作
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#define N 20
char arr[N] = "";

int main(int argc, char const *argv[])
{
    pid_t tip;
    int fd[2] = {};
    if (pipe(fd) != 0)
    {
        perror("pipe");
        return -1;
    }
    tip = fork();
    if (tip < 0)
    {
        perror("err");
        return -1;
    }
    else if (tip == 0)
    {
        while (1)
        {
            read(fd[0], arr, N);
            if (strcmp(arr, "quite") == 0)
            {
                break;
            }
            printf("%s\n", arr);
        }
        exit(0);
    }
    else
    {
        while (1)
        {

            scanf("%s", arr);
            write(fd[1], arr, strlen(arr) + 1);
            if (strcmp(arr, "quite") == 0)
            {
                break;
            }
        }
        wait(NULL);
    }
    return 0;
}
