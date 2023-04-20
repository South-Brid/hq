//fopen函数
#include <stdio.h>
void mycat();
int main(int argc, char const *argv[])
{
    mycat();
    return 0;
}
//老师得思路
void mycat()
{
    FILE *fp;
    fp = fopen("text.c","r");
    if (fp == NULL)
    {
        perror("text.c");
        return;
    }
    int ch;
    while (1)
    {
        ch = fgetc(fp);
        if (ch == EOF)
        {
            break;
        }
        else
        {
            printf("%c", ch);
        }
    }
    fclose(fp);
}