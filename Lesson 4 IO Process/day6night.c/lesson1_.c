//创建守护进程
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
int main(int argc, char const *argv[])
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return -1;
    }
    else if (pid == 0)
    {
        setsid();
        chdir("/");
        umask(0);
        for (int i = 0; i < 3; i++)
        {
            close(i);
        }
        while (1)
            ;
    }
    else
    {
        exit(0);
    }

    return 0;
}
