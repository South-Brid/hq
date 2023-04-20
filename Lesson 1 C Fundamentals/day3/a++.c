#include<stdio.h>
int main(int argc, char const *argv[])
{
    int a=5,b=6,c=7,d=8,m=2,n=2;
    (m=a<b)||(n=c>b);
    printf("%d %d",m,n);
    return 0;
}