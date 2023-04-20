#include <stdio.h>
int fun(char ch, char *pa);
int main(int argc, char const *argv[])
{
    char ch;
    char str[100] = {};
    puts("请输入字符");
    scanf("%c", &ch);
    puts("请输入字符串");
    scanf(" %[^\n]", str);
    int x = fun(ch, str);
    printf("字符%c的个数为%d\n", ch, x);
    return 0;
}
int fun(char ch, char *pa)
{
    int num = 0;
    while (*pa)
    {
        if (*pa == ch)
        {
            num++;
        }
        pa++;
    }
    return num;
}
