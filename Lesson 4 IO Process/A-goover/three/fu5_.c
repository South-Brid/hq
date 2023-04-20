//验证exit和_exit之间得区别
#include <stdlib.h>
#include <unistd.h>
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
    else if (pid == 0)
    {
        printf("in the child");
        exit(0);
        while (1)
            ;
    }
    else
    {
        printf("in the father");
        while (1)
            ;
    }
    return 0;
}
