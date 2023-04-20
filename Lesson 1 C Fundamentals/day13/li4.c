#include <stdio.h>
int add(int a, int b)
{
    return a + b;
}
int sum(int a, int b)
{
    return a - b;
}
int main(int argc, char const *argv[])
{
    int (*p_add)(int a, int b) = add;
    //函数指针 指针指向定义函数的地址
    printf("%d \n", p_add(10, 100));
    int (*s_sum)(int a,int b);
    s_sum=sum;
    printf("%d \n", s_sum(100, 90));
    printf("add的地址为：%p",add);
    //原来函数名是地址啊
    return 0;
}
