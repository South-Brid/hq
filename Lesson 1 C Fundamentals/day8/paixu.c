#include <stdio.h>
#define max 5
int *ch_arr();
int *babu(int *pb);
void pnt(int *pc);
int *chose(int *pd);

int main(int argc, char const *argv[])
{
    int *pa = ch_arr();
    pnt(chose(pa));
    return 0;
}
//选择排序函数
int *chose(int *pd)
{
    int i, j, k, m;
    for (i = 0; i < max - 1; i++)
    {
        k = i;
        for (j = i + 1; j < max; j++)
        {
            if (pd[j] < pd[k])
            {
                k = j;
            }
        }
        if (pd[k] != pd[i])
        {
            m = pd[k];
            pd[k] = pd[i];
            pd[i] = m;
        }
    }
    return pd;
}

//打印函数
void pnt(int *pc)
{
    int i, j;
    for (i = 0; i < max; i++)
    {
        printf("%d ", pc[i]);
    }
    puts(" ");
}
//冒泡排序
int *babu(int *pb)
{
    int i, j, k;
    for (i = 0; i < max - 1; i++)
    {
        for (j = 0; j < max - 1 - i; j++)
        {
            if (pb[j] > pb[j + 1])
            {
                k = pb[j];
                pb[j] = pb[j + 1];
                pb[j + 1] = k;
            }
        }
    }
    return pb;
}

//创建数组函数
int *ch_arr()
{
    static int str[max] = {0}; //局部变量的地址不能返回
    int i;
    for (i = 0; i < max; i++)
    {
        scanf("%d", &str[i]);
    }
    return str;
}
