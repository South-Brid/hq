//指针法
#include <stdio.h>
int main(int argc, char const *argv[])
{
    int s[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int x = sizeof(s) / sizeof(int);
    int *pa = s;
    int y;
    int *pb = s + x - 1;
    while (pa < pb)
    {
        y = *pa;
        *pa = *pb;
        *pb = y;
        pa++;
        pb--;
    }
    int i;

    for (i = 0; i < x; i++)
    {
        printf("%d ", s[i]);
    }
    return 0;
}
