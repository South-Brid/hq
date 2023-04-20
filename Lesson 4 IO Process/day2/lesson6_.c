//freopen进行文件得重新定向
#include<stdio.h>
int main(int argc, char const *argv[])
{
    //重定向
    printf("12333");
    //将后面得文件流重定向到文件中去
    freopen("6.txt","r+",stdout);
    printf("45666");
    freopen("/dev/tty","r+",stdout);
    printf("78999");
    return 0;
}
