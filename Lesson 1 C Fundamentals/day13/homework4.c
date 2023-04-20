//打印排列
#include <stdio.h>
void test(char ch, int x, int y)
{
    int i;
    int j;
    for (i = 0; i < y; i++)
    {
        for (j = 0; j < x; j++)
        {
            printf("%c ", ch);
        }
        puts("");
    }
}

int main(int argc, char const *argv[])
{
    char c;
    int a,b;
    puts("请依次输入想要打印的字符，字符个数，行数：");
    scanf("%c %d %d",&c,&a,&b);
    test(c, a, b);
    return 0;
}
