#include <stdio.h>
int main(int argc, char const *argv[])
{
    char a[10] = "acdgjmno";
    char b[10] = "befhil";
    char *pa = a;
    char *pb = b;
    while (*pa && *pb)
    {
        if (*pa < *pb)
        {
            putchar(*pa);
            pa++;
        }
        else
        {
            putchar(*pb);
            pb++;
        }
        if (*pa=='\0')
        {
            puts(pb);
        }
        if (*pb=='\0')
        {
            puts(pa);
        }
    }

    return 0;
}
