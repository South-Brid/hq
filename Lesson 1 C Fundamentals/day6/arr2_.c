#include <stdio.h>
int main(int argc, char const *argv[])
{
    //全部初始化
    int arr[5] = {1, 2, 3, 4, 5};//搜噶，
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    int brr[5] = {1, 2};
    for (int j = 0; j < 5; j++)
    {
        printf("%d ", brr[j]);
    }
    printf("\n");

    int crr[5];
    crr[0] = 1;
    for (int x = 0; x < 5; x++)
    {
        printf("%d ", crr[x]);
    }
     printf("\n");

    return 0;
}
