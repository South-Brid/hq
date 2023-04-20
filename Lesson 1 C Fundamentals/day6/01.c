#include <stdio.h>
#include<string.h>
int main(int argc, char const *argv[])
{
#if 0
    int i, j, z = 0;
    for (i = 1; i <= 1000; i++)
    {
        for (j = 1; j < i; j++)
        {
            if (i % j == 0)
            {
                z += j;
            }
        }
        if (z == i)
        {
            printf("%d ", z);
        }
        z = 0;
    }
    
    char ch;
    char arr[32] = "hello";
    int num = strlen(arr);
    for (int i = 0; i < num / 2; i++)
    {
        ch = arr[i];
        arr[i] = arr[num - 1 - i];
        arr[num - 1 - i] = ch;
    }
    printf("%s ", arr);
    return 0;
}
#endif
