#include <stdio.h>
#include <string.h>
int main(int argc, char const *argv[])
{
    int garde;
    scanf("%d", &garde);
    if (garde < 0 || garde > 100)//没有 ！> 和 ！<关系运算符
    {
        puts("erro");
    }
    else
    {
        if (garde > 60)
        {
            if (garde < 80)
            {
                puts("will");
            }
            else
            {
                puts("perfect");
            }
        }
        else
        {
            puts("bad");
        }
    }

    return 0;
}
