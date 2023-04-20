#include <stdio.h>
int main(int argc, char const *argv[])
{

    int arr[5] = {1, 2, 3, 4, 5};
    int i, j, k;
    for (i = 0; i < 5 - 1; i++)
    {
        for (j = 0; j < 5 - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                k = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = k;
            }
        }
    }

    for (i = 0; i < 5 ; i++)
        printf("%d ", arr[i]);

    return 0;
}
