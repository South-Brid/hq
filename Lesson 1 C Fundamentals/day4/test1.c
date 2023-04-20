#include <stdio.h>
int main(int argc, char const *argv[])
{
    int num;
    scanf("%d", &num);
    if (num >= 90 && num <= 100)
    {
        putchar(65);
        putchar(10);
    }
    else if (num >= 80 && num <= 89)
    {
        putchar(66);
        putchar(10);
    }
    else if (num >= 70 && num <= 79)
    {
        putchar(67);
        putchar(10);
    }
    else if (num >= 60 && num <= 69)
    {
        putchar(68);
        putchar(10);
    }
    else if (num > 100)
    {
        puts("?????");
    }
    else
    {
        puts("sorry you lost ");
    }
    return 0;
}
