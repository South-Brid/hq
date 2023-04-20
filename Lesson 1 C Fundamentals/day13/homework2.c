#include<stdio.h>

int sum_two(int num1,int num2)
{
    return num1 + num2 ;
} 
int char_two(int num1 ,int num2)
{
    return num1 - num2 ;
}
int  ji_two(int num1 ,int num2)
{
    return num1 * num2 ;
}
int chu_two(int num1 ,int num2)
{
    return num1 / num2 ;
}

//函数指针数组
int main(int argc, char const *argv[])
{
    int (*p[3])(int,int);
    p[0]=sum_two;
    p[1]=char_two;
    p[2]=ji_two;
    int (*pa)(int ,int);
    pa=chu_two;
//函数指针
    printf("%d",pa(8,2));
    return 0;
}
