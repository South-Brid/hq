#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        perror("err");
        return -1;
    }
    else if (pid == 0)
    {
        printf("child %d %d \n", getpid(), getppid());
    }
    else
    {
        printf("partent %d %d \n", pid, getpid());
    }
    return 0;
}
