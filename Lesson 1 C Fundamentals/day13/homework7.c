#include<stdio.h>
int add(int a,int b)
{
    return a+b;
}
int subtract(int a,int b)
{
    return a-b;
}
int multiplication(int a,int b)
{
    return a*b;
}
int chu(int a,int b)
{
    return a/b;
}
int pros(int(*p)(int,int),int a,int b)
{
    return p(a,b);
}

int main(int argc, char const *argv[])
{
    int x = pros(add,9,100);
    int y = pros(subtract,100,9);
    int z = pros(multiplication,2,50);
    int t = pros(chu,8,2);

    printf("%d %d %d %d",x,y,z,t);
    return 0;
}
