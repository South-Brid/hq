//利用数组指针传参求和
#include<stdio.h>
int a_sum(int (*p)[4],int n)
//行省略了，所以需要传行的值
{
    int i,j,sum=0;
    for ( i = 0; i < n; i++)
    {
        for ( j = 0; j < 4; j++)
        {
            sum+=p[i][j];
        }
    }
    return sum;
}

int main(int argc, char const *argv[])
{
    int a[3][4]={7,10,-2,3,14,30,6,-15,0,5,27,-7};
    printf("%d ",a_sum(a,3));
    return 0;
}
