#include<stdio.h>
int main(int argc, char const *argv[])
{   int arr[15]={1,1};
    for (int i=0;i<13;i++)
    {
        arr[i+2]=arr[i]+arr[i+1];
    }
    for (int j = 14; j >= 0; j--)
    {
        printf("%d ",arr[j]);
    }
    
    return 0;
}
