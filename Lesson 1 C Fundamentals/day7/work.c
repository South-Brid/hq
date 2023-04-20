#include <stdio.h>
#define MAX 5
void maopao(int *pa);
void chose(int *pb);
int main(int argc, char const *argv[])
{
    int arr[MAX] = {0};
    int i;
    for (i = 0; i < MAX; i++)
    {
        scanf("%d", &arr[i]);
    }
    //maopao(arr);
    chose(arr);
    return 0;
}
//函数
void maopao(int *pa)
{
    int i, j, mid;
    for (i = 0; i < MAX - 1; i++)
    {
        for (j = 0; j < MAX - 1 - i; j++)
        {
            if (pa[j] > pa[j + 1])
            {
                mid = pa[j];
                pa[j] = pa[j + 1];
                pa[j + 1] = mid;
            }
        }
    }
    for (i = 0; i < MAX; i++)
    {
        printf("%d ", pa[i]);
    }
}

//选择
void chose(int *pb)
{
    int i, j, k, ch;
    for (i = 0; i < MAX - 1; i++)
    {
        k = i;
        for (j = i + 1; j < MAX; j++)
        {
            if (pb[j] < pb[k])
            {
                k = j;
            }
        }
        if (pb[k] != pb[i])
        {
            ch = pb[k];
            pb[k] = pb[i];
            pb[i] = ch;
        }
    }
    for (i = 0; i < MAX; i++)
    {
        printf("%d ", pb[i]);
    }
}

//??????

