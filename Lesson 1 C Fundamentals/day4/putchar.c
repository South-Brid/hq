#include<stdio.h>
int main(int argc, char const *argv[])
{
    int x=getchar();
    printf("%d\n",x);
    putchar(x);//使用putchar接受getchar的返回值
    putchar(10);//()括号是putchar
    return 0;
}

