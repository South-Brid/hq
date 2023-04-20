//验证进程之间得独立性
#include <stdio.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    pid_t pid;
    int i = 0;
    pid = fork();
    if (pid == -1)
    {
        perror("err");
        return -1;
    }
    else if (pid == 0)
    {
        i++;
        printf("chaild:%d\n", i);
        printf("child \n");
        while (1)
            ;
    }
    else
    {
        i=i+55;
        printf("partent:%d\n", i);
        printf("partent \n");
        while (1)
            ;
    }
    return 0;
}
