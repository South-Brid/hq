//使用标准IO中得fgetc和fputc实现cp功能
#include <stdio.h>
int main(int argc, char const *argv[])
{
    FILE *fp;
    FILE *fw;
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
    char ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        fputc(ch,fw);
    }
    fclose(fp);
    fclose(fw);
    return 0;
}
