//fgets函数
#include <stdio.h>
void fg();
int main(int argc, char const *argv[])
{
    fg();
    return 0;
}

void fg()
{
    FILE*fp;
    char str[10];//定义字符数组用与接受输出
    fp=fopen("text.c","r");
    if (fp == NULL)
    {
        perror("text.c");
        return;
    }
    printf("%s",fgets(str,4,fp));
    //fputs("str", stdout);
}
