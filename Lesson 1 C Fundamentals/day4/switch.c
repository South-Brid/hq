#include<stdio.h>
int main(int argc, char const *argv[])
{
    int num;
    scanf("%d",&num);
    switch(num)//（）内部不能是浮点型和字符串
    {
        case 1:
        puts("hello");
        break;
        case 2:
        puts("world");
        break;
        default:
        puts("other");
        break;
    }
    return 0;
}
