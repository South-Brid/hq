#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

pid_t pid;
void conductor(int arg)
{
    if (arg == SIGINT)
    {
        kill(getppid(), SIGUSR1);
    }
    else if (arg == SIGQUIT)
    {
        kill(getppid(), SIGUSR2);
    }
    else if (arg == SIGUSR1)
    {
        printf("plese get off the bus\n");
        exit(0);
    }
}

void bus(int arg)
{
    if (arg == SIGUSR1)
    {
        printf("lets gogogo\n");
    }
    else if (arg == SIGUSR2)
    {
        printf("stop the bus\n");
    }
    else if (arg == SIGTSTP)
    {
        kill(pid, SIGUSR1);
        wait(NULL);
        exit(0);
    }
}

int main(int argc, char const *argv[])
{
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return -1;
    }
    else if (pid == 0)
    {
        signal(SIGTSTP, SIG_IGN);

        signal(SIGINT, conductor);
        signal(SIGQUIT, conductor);
        signal(SIGUSR1, conductor);
    }
    else
    {
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);

        signal(SIGUSR1, bus);
        signal(SIGUSR2, bus);
        signal(SIGTSTP, bus);
    }
    while (1)
        ;
    pause();
    return 0;
}
