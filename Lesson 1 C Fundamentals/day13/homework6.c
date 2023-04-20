#include <stdio.h>
char *is_with(char *pa, char *pb)
{
    char *pc = pa;
    while (*pa)
    {

        if (*pa == *pb)
        {
            return pa;
        }
        pa++;
    }
    return NULL;//谨慎使用else
}
int main(int argc, char const *argv[])
{
    char ch;
    puts("请输入要查找的字符：");
    scanf("%c", &ch);

    char a[100] = {};
    puts("请输入字符串：");
    scanf(" %[^\n]", a);

    char *s = is_with(a, &ch);

    if (s != NULL)
    {
        printf("在输入的字符串找到了%c\n", *s);
    }
    else
    {
        printf("没有找到\n");
    }

    return 0;
}
