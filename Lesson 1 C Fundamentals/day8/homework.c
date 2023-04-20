#include <stdio.h>
#include <string.h>
int main(int argc, char const *argv[])
{

    char arr[] = "i love china";
    int num = strlen(arr);
    //倒序打印i love china
    char *pa = arr;
    char *pb = pa + num - 1;
    char ch;
    while (pa < pb)
    {
        ch = *pa;
        *pa = *pb;
        *pb = ch;
        pa++;
        pb--;
    }
    //倒序anihc
    int sz = 0;
    char *pc = arr;
    char *pd = arr;
    while (*pd != ' ')
    {
        pd++;
        sz++;
    }
    pd--;
    while (pc < pd)
    {
        ch = *pc;
        *pc = *pd;
        *pd = ch;
        pc++;
        pd--;
    }
    //倒序打印evol
    char *pe = arr + sz + 1;
    char *pr = arr + sz + 1;
    while (*pr != ' ')
    {
        pr++;
    }
    pr--;
    while (pe < pr)
    {
        ch = *pe;
        *pe = *pr;
        *pr = ch;
        pe++;
        pr--;
    }

    printf("%s\n", arr);
    return 0;
}
