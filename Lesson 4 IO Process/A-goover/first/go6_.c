//使用标准IO完成读取文件行数操作
#include <stdio.h>
#include <string.h>
int main(int argc, char const *argv[])
{
    FILE *fp;
    char arr[20];
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        perror(argv[1]);
        return -1;
    }
    int num = 1;
    while (fgets(arr, 20, fp) != NULL)
    {
        if (arr[strlen(arr) - 1] == '\n')
        {
            num++;
        }
    }
    printf("hangshu is %d \n", num);
    fclose(fp);
    return 0;
}
