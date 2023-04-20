#include<stdio.h>
int main(int argc, char const *argv[])
{
    int arr[5];//数据类型 表明是定义
    //连续存放
    printf("%p\n",arr);
    printf("%p\n",&arr[0]);
    printf("%p\n",&arr[1]);//没有数据类型是使用
    printf("%p\n",&arr[2]);
    printf("%p\n",&arr[3]);
    printf("%p\n",&arr[4]);
    return 0;
}
