#include<stdio.h>
int main()
{
    int arr[10][10]={0};
    int i,j;

    for(i=0;i<10;i++)
    {
        arr[i][0]=1;    
        printf("%d ",arr[i][0]);//第一行特殊单独拿出来打印
        for(j=1;j<=i;j++)
        {
                arr[i][j]=arr[i-1][j-1]+arr[i-1][j];
                printf("%d ",arr[i][j]);
        }
        putchar('\n');
    }
    return 0;
}
