#include <stdio.h>
#include <strings.h>
int main(int argc, char const *argv[])
{
    int i;
    int arr[5] = {1, 2, 3, 4, 5};
    for (i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }
    puts("");
    bzero(arr, sizeof(arr));
    for (i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }
    puts("");
    return 0;
}
