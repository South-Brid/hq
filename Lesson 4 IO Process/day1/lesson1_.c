//缓存区得大小计算
#include <stdio.h>
//使用stdout进行计算
void stdout1();
//使用循环进行计算
void myself();
//整形计算方式
void IntOut();
int main(int argc, char const *argv[])
{
    stdout1();
    return 0;
}

//整形计算方式
void IntOut()
{
    for (int i = 0; i < 300; i++)
    {
        printf("%4d",i);
    }
    while(1);
}
//使用stdout进行计算
void stdout1()
{
    printf("hello");
    printf("%d", stdout->_IO_buf_end - stdout->_IO_buf_base);
}
//使用循环进行计算
void myself()
{
    int i = 0;
    scanf("%d", &i);
    for (int j = 0; j <= i; j++)
    {
        printf("a");
    }
    while (1) ;
}