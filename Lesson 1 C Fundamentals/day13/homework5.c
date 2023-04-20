#include <stdio.h>
void paixu(int **pr, int *pb)
{
    int x=0;
    x = (*pr)[*pb];
    (*pr)[*pb] = (*pr)[*pb + 1];
    (*pr)[*pb + 1] = x;
    //必须得加括号，因为优先级的问题*pr[i]会先计算pr[i]
}

void babu(int *p, int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - 1 - i; j++)
            if (p[j] > p[j + 1])//先写条件进行判断，符合条件才会进入函数
                paixu(&p, &j);//提升代码效率      
}

int main(int argc, char const *argv[])
{
    int a[] = {95, 32, 67, 85, 73, 18};
    int x = sizeof(a) / sizeof(int);
    babu(a, x);
    int i;
    for (i = 0; i < x; i++)
    {
        printf("%d ", a[i]);
    }
    return 0;
}
