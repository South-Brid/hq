//waitpid
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include<time.h>
int main(int argc, char const *argv[])
{
    pid_t pid;
    pid = fork();
    if (pid == -1)
    {
        perror("err");
        return -1;
    }
    else if (pid == 0)
    {
        sleep(1);
        printf("in the child \n");
        exit(0);
    }
    else
    {
        
        printf("in the partent\n");
        waitpid(-1, NULL, 0);//只能放在父进程
        while (1)
            ;
    }

    return 0;
}
