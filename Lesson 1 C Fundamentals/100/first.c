#include <stdio.h>
#include <math.h>
void suanfa_01();
void pingfang();
int main(int argc, char const *argv[])
{
#if 0
    suanfa_01();
#endif
    pingfang();
    return 0;
}

//3.一个整数，它加上100后是一个完全平方数，再加上168又是一个完全平方数，请问该数是多少？
void pingfang()
{
    int x, y;
    int  i;
    for (i = 0; i < 10000; i++)
    {
        x = sqrt(i + 100);
        y = sqrt(i + 168);//用-lm
        if (pow(x, 2) == i && pow(y, 2) == i)
        {
            printf("%d ", i);
        }
    }
}

//1.有1、2、3、4个数字，能组成多少个互不相同且无重复数字的三位数？都是多少？
//先排列后去除
void suanfa_01()
{
    int i, j, k;
    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
            for (k = 0; k < 5; k++)
                if (i != j && i != k && j != k)
                //核心语句
                {
                    printf("%d%d%d ", i, j, k);
                }
}
