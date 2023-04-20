#include <stdio.h>
int main(int argc, char const *argv[])
{
    char arr[50] = {};
    scanf("%[^\n]", arr);
    int bar[50] = {};
    char *pa = arr;
    int num = 0;
    int i = 0;
    while (*pa)
    {
        if (*pa < '0' || *pa > '9')
        {
            pa++;
            continue;
        }
        while (*pa >= '0' && *pa <= '9')
        {
            num = num * 10 + *pa - '0';
            pa++;
        }
        bar[i] = num;
        i++;
        num = 0;
    }

    printf("number is %d \n", i);
    int x;
    for (x = 0; x < i; x++)
    {
        printf("%d\n", bar[x]);
    }
    return 0;
}
