//使用标准IO中得fgets和fputs实现cp功能
#include <stdio.h>
int main(int argc, char const *argv[])
{
    FILE *fp;
    FILE *fw;
    char arr[10];
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        perror(argv[1]);
        return -1;
    }
    fw = fopen(argv[2], "w");
    if (fp == NULL)
    {
        perror(argv[2]);
        return -1;
    }
    while (fgets(arr, 10, fp) != NULL)
    {
        fputs(arr,fw);//error,复习时出现问题
    }

    return 0;
}
