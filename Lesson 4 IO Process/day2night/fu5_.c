//fopen重定向问题
#include<stdio.h>
int main(int argc, char const *argv[])
{
    printf("123456");
    freopen("fu1.txt","w",stdout);//
    printf("45631257");
    freopen("/dev/tty","w",stdout);//重新定向到终端
    printf("45631257");
    return 0;
}
