//return 和 exit 得区别
#include <stdio.h>
#include <stdlib.h>
void add();
int main(int argc, char const *argv[])
{
    add();
    puts("welcome new world");
    return 0;
}

void add()
{
    puts("hello world");
    exit(0);
}
