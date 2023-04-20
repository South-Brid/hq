//打印颠倒的图案
#include <stdio.h>
int main(int argc, char const *argv[])
{
    int i, j, num;
    scanf("%d", &num);
    for (i = 0; i < num; i++)
    {
        for (j = 0; j < i + 1; j++)
        {
            printf("*");
        }
        puts(" ");
    }
    int x, y, z;              //定义3个变量xyz
    for (x = 0; x < num; x++) //循环num次
    {
        for (y = 0; y < x; y++) //先打印空格
        {
            printf(" ");
        }
        for (z = num; z > x; z--) //再打打印字符
        {
            printf("*");
        }
        puts(" ");
    }

    return 0;
}
