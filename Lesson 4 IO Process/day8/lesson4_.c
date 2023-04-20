#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
void handly(int arg)
{
    if (arg == 2)
    {
        printf("arg is %d \n", arg);
        printf("SIGINT\n");
    }
    else
    {
        printf("arg is %d \n", arg);
        printf("SIGTSTP\n");
    }
}

int main(int argc, char const *argv[])
{
    //忽略操作
    //signal(SIGINT,SIG_IGN);
    //缺省操作
    //signal(SIGINT,SIG_DFL);//执行默认操作
    //捕捉操作
    signal(SIGINT, handly);
    signal(SIGTSTP, handly);//捕捉SIGTSTP 
    pause();
    return 0;
}
