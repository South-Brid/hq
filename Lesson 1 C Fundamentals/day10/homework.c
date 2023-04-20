#include <stdio.h>
void homework(char *pa);
int main(int argc, char const *argv[])
{
    char arr[100] = {};
    scanf("%[^\n]", arr);
    homework(arr);
    return 0;
}

void homework(char *pa)
{
    int brr[100] = {0};
    int i = 0;
    int x = 0;
    int *pb = brr;
    while (*pa)
    {
        if (*pa < '0' || *pa > '9')
        {
            pa++;
            //指针偏移，向后移动
            continue;
        }

        int sum = 0;
        while (*pa >= '0' && *pa <= '9')
        {
            sum = sum * 10 + *pa - '0';
            pa++;
        }
        brr[i] = sum;
        sum = 0;
        i++;
    }
    printf("%d\n", i);
    while (x < i)
    {
        printf("%d ", brr[x]);
        x++;
    }
}