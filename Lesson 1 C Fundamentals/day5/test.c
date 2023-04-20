//交换排序
#include<stdio.h>
int main(int argc, char const *argv[])
{
    int a,b,c,d;
    scanf("%d %d %d",&a,&b,&c);
    if (a<b)
    {
        d=a;
        a=b;
        b=d;
    }
    if(a<c)
    {
        d=a;
        a=c;
        c=d;
    }
    if(b<c)
    {
        d=b;
        b=c;
        c=d;
    }
    printf("%d>%d>%d\n",a,b,c);
    return 0;
}
