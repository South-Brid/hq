//成绩判断
#include <stdio.h>
int main(int argc, char const *argv[])
{
    int garde;
    scanf("%d", &garde);
    garde /= 10;

    if (garde > 10)
    {
        puts(" what's wrong with you? ");
        return 0;
    }

    switch (garde)
    {
    case 10:
    case 9:
        putchar(65);
        putchar(10);
        break;
    case 8:
        putchar(66);
        putchar(10);
        break;
    case 7:
        putchar(67);
        putchar(10);
        break;
    case 6:
        putchar(68);
        putchar(10);
        break;
    default:
        puts("sorry you lost");
        putchar(10);
        break;
    }
    return 0;
}
