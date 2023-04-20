//计算标准输出缓存区大小
#include<stdio.h>
int main(int argc, char const *argv[])
{
    for (int i = 0; i < 300; i++)
    {
        printf("%4d",i);
    }
    while(1);
    return 0;
}