#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <signal.h>

pid_t pid;

int main(int argc, char const *argv[])
{

    if ((pid = fork()) < 0)
    {
        perror("fork");
        return -1;
    }
    else if (pid == 0) //售票员
    {
        signal(SIGINT, conductor);
        signal(SIGQUIT, conductor);
    }
    else //司机
    {
        signal(SIGUSR1, driver)
    }

    return 0;
}
void driver(int value)
{
    if (value == SIGUSR1)
    {
        printf("let,s gogogo\n");
    }
}

void conductor(int value)
{
    if (value == SIGINT)
    {
        kill(getppid(), SIGUSR1)
    }
    else if (value == SIGQUIT)
    {
         kill(getppid(), SIGUSR2)
    }
}