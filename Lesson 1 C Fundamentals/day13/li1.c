#include <stdio.h>
int main(int argc, char const *argv[])
{
    int *p[3];
    int a[3] = {1, 2, 3};
    int b[3] = {4, 5, 6};
    int c[3] = {7, 8, 9};
    p[0] = b;
    p[1] = a;
    p[2] = c;
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            printf("%d ", *(*(p + i) + j));
        }
    }
    return 0;
}
