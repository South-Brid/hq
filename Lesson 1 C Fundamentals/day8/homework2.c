#include <stdio.h>
int main(int argc, char const *argv[])
{
    int s[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int x;
    int sz = sizeof(s) / sizeof(int);
    int *pa = s;
    int *pb = s + sz - 1;
    while (pa < pb)
    {
        x = *pa;
        *pa = *pb;
        *pb = x;
        pa++;
        pb--;
    }
    int i;
    for (i = 0; i < sz; i++)
    {
        printf("%d ", s[i]);
    }
    return 0;
}
