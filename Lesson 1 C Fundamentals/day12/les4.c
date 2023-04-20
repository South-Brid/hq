//选择排序法
#include <stdio.h>
int main(int argc, char const *argv[])
{

    int s[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int i, j, x, y;
    for (i = 0; i < 8 - 1; i++)
    {
        x = i;
        for (j = i + 1; j < 8; j++)
        {
            if (s[j] > s[x])
            {
                x = j;
            }
        }
        if (i != x)
        {
            y = s[i];
            s[i] = s[x];
            s[x] = y;
        }
    }
    for (i = 0; i < 8; i++)
    {
        printf("%d ", s[i]);
    }
    return 0;
}