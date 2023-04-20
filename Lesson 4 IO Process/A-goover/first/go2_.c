//使用标准IO中得getc实现cat功能
#include <stdio.h>
int main(int argc, char const *argv[])
{
    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        perror(argv[1]);
        return -1;
    }
    char ch;
    while ((ch=fgetc(fp))!=EOF)
    {
        printf("%c", ch);
    }
    fclose(fp);
    return 0;
}
