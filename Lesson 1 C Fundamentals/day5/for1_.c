#include<stdio.h>
#include<string.h>
int main(int argc, char const *argv[])
{
    int i = 1;
    for(;i<10;)//++i后i的值会变化
    //++i和i++在赋值给别的变量的时候才会不同
    {
        printf("%d",i);
        i++;
    }
    puts("");
    return 0;
}
