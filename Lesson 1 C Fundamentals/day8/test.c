#include <stdio.h>
#define N 5

//函数声明
int *babu(int *pa);
void print(int *pb);
int *chose(int *pc);
int *arr();
void tao();
void sanjiao();

int main(int argc, char const *argv[])
{
#if 0
    int *a = arr();
    int *b = chose(a);
    b = babu(a);
    print(b);
    tao();
#endif
    sanjiao();
    return 0;
}

//函数定义
//数组函数
int *arr() //又忘记了不能返回局部变量的地址
{
    static int a[N] = {7, 6, 5, 4, 9};
    return a;
}

//冒泡排序
int *babu(int *pa)
{
    int i, j, k;
    for (i = 0; i < N - 1; i++)
        for (j = 0; j < N - 1 - i; j++)
            if (pa[j] > pa[j + 1])
            {
                k = pa[j];
                pa[j] = pa[j + 1];
                pa[j + 1] = k;
            }
    return pa;
}

//打印结果
void print(int *pb)
{
    int i;
    for (i = 0; i < N; i++)
    {
        printf("%d ", pb[i]);
    }
}

//选择排序
int *chose(int *pc)
{
    int i, j, k, l;
    for (i = 0; i < N - 1; i++)
    {
        k = i;
        for (j = i + 1; j < N; j++)
            if (pc[j] < pc[k])
            {
                k = j;
            }
        if (pc[k] != pc[i])
        {
            l = pc[k];
            pc[k] = pc[i];
            pc[i] = l;
        }
    }
    return pc;
}

//猴子吃桃子问题
void tao()
{
    int arr[10] = {0};
    arr[9] = 1;
    //第十天桃子为1
    int i;
    for (i = 9; i > 0; i--)
    {
        arr[i - 1] = (arr[i] + 1) * 2;
        //根据第九天桃子为4,推出
    }
    printf("%d", arr[0]);
}

//
void sanjiao()
{
    int arr[10][10] = {0};
    int i, j, ch;
    for (i = 0; i < 10; i++)
    {
        arr[i][0] = 1;
        for (j = 1; j <= i; j++)
        {
            arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
        }
    }
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j <= i; j++)
    {
        printf("%d ",arr[i][j]);

    }
    puts("");
    }

}
