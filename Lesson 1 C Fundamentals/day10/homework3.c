#include <stdio.h>
int main(int argc, char const *argv[])
{
    char arr[50] = {};
    int brr[55] = {0};
    scanf("%[^\n]", arr);
    char *pa = arr;
    int i = 0;
    int num = 0;
    while (*pa)
    {
        if (*pa > '9' || *pa < '0')
        {
            pa++;
            continue;
        }

        while (*pa >= '0' && *pa <= '9')
        {
            num = num * 10 + *pa - '0';
            pa++;
        }
        brr[i] = num;
        num = 0;
        i++;
    }
    printf("数字共有%d处", i);
    int j;
    for (j = 0; j < i; j++)
    {
        printf("数值为%d ", brr[j]);
    }

    return 0;
}
