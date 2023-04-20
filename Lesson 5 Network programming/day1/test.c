//冒泡排序-从小到大进行排序
#define N 10
#include<stdio.h>
int main(int argc, char const *argv[])
{
    int arr[N]={9,8,7,6,5,4,3,2,1,0};
    for (int i = 0; i < N-1; i++)
    {
        for (int j = 0; j < N-1-i; j++)
        {
            if (arr[j]>arr[j+1])
            {
                arr[j]=arr[j]+arr[j+1];
                arr[j+1]=arr[j]+arr[j+1];
                arr[j]=arr[j]+arr[j+1];
            }
        }
    }
    for (int i = 0; i < N; i++)
    {
        printf("%d ",arr[i]);
    }
    return 0;
}