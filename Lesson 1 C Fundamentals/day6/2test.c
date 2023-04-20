#include <stdio.h>
int main(int argc, char const *argv[])
{
    int x;
    scanf("%d", &x);
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < i + 1; j++)
        {
            printf("*");
        }
        printf("\n");
    }
    int a, b, c;
    for (a = 0; a < x; a++)
    {
        for (b = 0; b < a; b++)
        {
            printf(" ");
        }
        for ( c = x; c > a; c--)
        {
            printf("*");
        }
        printf("\n");
    }
    return 0;
}
