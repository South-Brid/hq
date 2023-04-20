#include <stdio.h>
int main(int argc, char const *argv[])
{

    int j;
    int x;
    int z = 0;
    for (j = 1; j < 1000; j++)//创建1-1000 j
    {

        for (x = 1; x < j; x++)
        //创建被处数 x,x总是小于除数j
        {
            if (j % x == 0)//当能除尽的时候
                z += x;//将x的值累加到z上
        }
        //x的值累加完成后跳出x的循环
        if (z == j)//判断累加值z和j
        {
            printf("%d ", z);
        }
        z = 0;//将z初始化为了下次循环做准备
    }
    return 0;
}
