#include<stdio.h>
//倒推出来
int main(int argc, char const *argv[])
{
    int arr[15] = {1,1};
    for (int i = 2; i < 15; i++)
    {
        arr[i]=arr[i-1]+arr[i-2];
    }
    for ( int j = 14; j >=0; j--)
    {
        printf("%d ",arr[j]);
    }
    return 0;
}
