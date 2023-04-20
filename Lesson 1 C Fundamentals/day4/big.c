#include<stdio.h>
int main(int argc, char const *argv[])
{
    int x;
    x=getchar();
    if(x >= 65 && x <= 90)
    {
        x+=32;
        putchar(x);
        putchar(10);
    }
    else if(x >=97 && x<= 122)
    {
        x-=32;
        putchar(x);
        putchar(10);
    }
    else
    {
        puts("erro");
    }
    return 0;
}
