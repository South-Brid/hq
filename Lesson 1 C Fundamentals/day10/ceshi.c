#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int func(int a)
{
    if (a == 1)
    {
        return 1;
    }
    else
    {
        return a *func(a - 1);
    }
}
int main()
{
    printf("%d",func(5));
    return 0;
}