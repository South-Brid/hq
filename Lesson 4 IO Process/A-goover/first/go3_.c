//使用标准io中得fgets实现mycat
#include <stdio.h>
int main(int argc, char const *argv[])
{
    FILE *fp;
    char arr[10];
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        perror(argv[1]);
        return -1;
    }
    while (fgets(arr, 10, fp) != NULL)
    {
        printf("%s", arr);
    }
    return 0;
}
