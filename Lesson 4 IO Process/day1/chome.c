#include <stdio.h>
void mystrlen();
int myfunc(char ch, char *p);
int main(int argc, char const *argv[])
{
    //mystrlen();
    char arr[]="hehhhheeheheh";
    printf("%d",myfunc('h',arr));
    return 0;
}
//计算字符数
int myfunc(char ch, char *p)
{
    int i = 0;
    while (*p)
    {
        if (*p == ch)
            i++;
        p++;
    }
    return i;
}

//我的stlen
void mystrlen()
{
    char arr[] = "hello world";
    char *pa = arr;
    int i = 0;
    while (*pa)
    {
        i++;
        pa++;
    }
    printf("%d", i);
}
