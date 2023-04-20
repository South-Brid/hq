#include<stdio.h>
int add(int a,int b)
{
    return a+b;
}
int jian(int a,int b)
{
    return a-b;
}
int cheng(int a,int b)
{
    return a*b;
}
int huidiao(int(*p)(int,int),int a,int b)
{
    return p(a,b);
}

int main(int argc, char const *argv[])
{
    int x = huidiao(jian,5,3);
    printf("%d \n",x);
    return 0;
}
