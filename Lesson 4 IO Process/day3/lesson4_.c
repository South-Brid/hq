#include <stdio.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{   int a=1;
    pid_t pid = -3;
    pid = fork();
    puts("8958419");
    if (pid < 0)
    {
        perror("pid");
        return -1;
    }
    else if(pid == 0)
    {   a++;
        printf("in the child\n");
        // while(1);
    }
    else
    {
        printf("in the parent\n");
        // while(1);
    }
    printf("%d\n",a);
    return 0;
}
