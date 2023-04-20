//使用标准io实现cp功能
#include <stdio.h>

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("%s <newname> <oldname> \n", argv[0]);
        return -1;
    }
    FILE *fp;
    FILE *ft;
    char arr[10];
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        perror(argv[1]);
        return -1;
    }
    ft = fopen(argv[2], "w");
    if (ft == NULL)
    {
        perror(argv[2]);
        return -1;
    }
    while (fgets(arr,10,fp))
    {
        fputs(arr,ft);
    }
    fflush(fp);
    fflush(ft);
    return 0;
}
