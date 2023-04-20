#include<stdio.h>
extern int n;
extern void func();
int main(int argc, char const *argv[])
{
    printf("%d\n",n);
    func();
    return 0;
}
