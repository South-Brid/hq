#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int func()
{
    printf("this is func\n");
    exit(0);
    return 0;
}
int main(int argc, char const *argv[])
{
    printf("in main");
    //func();
   // printf("after fun\n");//刷新缓存区
   _exit(0);//不刷新缓存区
   while(1);
    return 0;
}
