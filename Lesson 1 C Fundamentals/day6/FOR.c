//必考试
#include <stdio.h>
#include<string.h>
int main(int argc, char const *argv[])
{
    int add = 0;
    char buf[32] = "hello";
    char ch;
    //for (add = 0; buf[add] != '\0'; add++);
    //for循环还能这么用！！！
    add=strlen(buf);
    int j = 0;
    while (j < add)
    {
        ch = buf[j];
        buf[j] = buf[add - 1];
        buf[add - 1] = ch;
        add--;
        j++;
    }
#if 0
    for (int k = 0; k < add/2; k++)
    {
        ch=buf[k];
        buf[k]=buf[add-1-k];
        buf[add-1-k]=ch;
    }
#endif

    printf("%s ", buf);

    return 0;
}
