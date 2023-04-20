//文件重定向问题
#include<stdio.h>
int main(int argc, char const *argv[])
{
    printf("hello world\n");
    freopen("2.txt","w",stdout);
    printf("114514\n");
    freopen("/dev/tty","w",stdout);
    printf("hello world");
    return 0;
}
