//创建一个守护进程
#include <stdio.h>
int main(int argc, char const *argv[])
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        perror("err");
        return -1;
    }
    else if (pid == NULL)
    {
        setsid();
        chdir('/');
        uumask(0);
        for (int i = 0; i < 3; i++)
        {
            close(i);
        }
        while(1);
    }
    else
    {
        exit(0);
    }
    return 0;
}
