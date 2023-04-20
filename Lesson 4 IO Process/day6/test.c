//函数指针
#include<stdio.h>
int add(int x,int y)
{
    return x+y;
}

int sub(int x,int y)
{
    return x-y;
}

int test(int (*p)(int,int),int x,int y)
{
    printf("%d ",p(x,y));
    return 0;
}
int main(int argc, char const *argv[])
{
    // int (*p)(int , int);//函数指针得妙用
    // p=sub;//大型工程减小修改
    // printf("%d \n",p(3,4));
    test(add,3,10);
    return 0;
}
