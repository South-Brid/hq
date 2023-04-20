#include<stdio.h>
int main(int argc, char const *argv[])
{
    printf("hello world");
    freopen("1.txt","w+",stdout);
    printf("welcome new world");
    freopen("/dev/tty","a",stdout);
    printf("eeeeeeeee");
    return 0;
}
