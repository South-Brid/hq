//面试题目,宏函数
#include<stdio.h>
#define MAX(a,b) a>b?a:b//宏函数
int main(int argc, char const *argv[])
{
    printf("%d\n",MAX(11,3));
    return 0;
}
