#include <stdio.h>
#include <string.h>
int main(int argc, char const *argv[])
{
    int arr[5] = {1, 2, 3, 4, 5};
    memset(arr, 0, sizeof(arr));
    //0是给每一个字节复制
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}
