//冒泡排序法
#include <stdio.h>
int main(int argc, char const *argv[])
{
    int s[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int i, j, z;
    for (i = 0; i < 7; i++)
        for (j = 0; j < 8 - 1 - i; j++)
        {
            if (s[j] < s[j + 1])
            {
                z = s[j];
                s[j] = s[j + 1];
                s[j + 1] = z;
            }
        }
    for (i = 0; i < 8; i++)
    {
        printf("%d ", s[i]);
    }

    return 0;
}
