//字符串相接
#include<stdio.h>
#include<string.h>
int main(int argc, char const *argv[])
{
    char str1[20]="hello ",str2[20]="world！";
    //strcat(str1,str2);
    #if 1
    char *pa =str1,*pb=str2;
    while (*pa)
    pa++;
    while (*pb)
    {
        *pa=*pb;
        pa++;
        pb++;
    }
    *pa=*pb;//把‘\0’也传送过去
    #endif
    puts(str1);
    return 0;
}
