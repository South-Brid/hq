#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
char arr[32] = "";
int main()
{
    int fd[2] = {};
    if (pipe(fd) < 0)
    {
        perror("pipe");
        return -1;
    }
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return -1;
    }
    else if (pid == 0)
    {
        while (1)
        {
            read(fd[0], arr, 32);
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
            write(fd[1], arr, 32);
            if (strcmp(arr, "quite") == 0)
            {
                break;
            }
        }
        wait(NULL);
        exit(0);
    }
}