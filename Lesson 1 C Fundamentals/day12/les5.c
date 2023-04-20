#include<stdio.h>
int main(int argc, char const *argv[])
{
    int a[8] ={1,2,3,4,5,6,7,8};
    int *p =a;
    int *q =a+7;
    while (p<q)
    {
      *p=*p+*q;
      *q=*p-*q;
      *p=*p-*q;
        p++;
        q--;
    }
    int i;
    for ( i = 0; i < 8; i++)
    {
        printf("%d ",a[i]);
    }
    return 0;
}
