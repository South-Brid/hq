#include <stdio.h>
#include <time.h>
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
        setsid();
        chdir("/");
        umask(0);
        for (int i = 0; i < 3; i++)
        {
            close(i);
        }
        printf("i am child\n");
        while (1)
            ;
    }
    else
    {

        printf("i am parents\n");
        while (1)
            ;
    }
    return 0;
}
