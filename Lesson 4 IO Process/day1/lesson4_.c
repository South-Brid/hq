//fputc
#include <stdio.h>
void fputc1();
int main(int argc, char const *argv[])
{
    fputc1();
    return 0;
}

void fputc1()
{
    FILE *fp;
    fp = fopen("text.c", "a");
    if (fp == NULL)
    {
        perror("fp:");
        return;
    }
    //只能写一个
    printf("%c",fputc('a', fp));
    fputc('a', stdout);//向终端写入一个字符
}