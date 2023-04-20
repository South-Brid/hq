#include<stdio.h>
int main(int argc, char const *argv[])
{
    int x;
    x=getchar();
    if(x >= 65 && x <= 90)
    {
        putchar(x+32);
        putchar(10);
        return 0;
    }
    if(x >=97 && x<= 122)
    {
        putchar(x-32);
        putchar(10);
    }
    else
    {
        puts("erro");
    }
    return 0;
}
