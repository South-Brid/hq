#include <stdio.h>

char *fistfun(char *pa, char *pb);
char *twofist(char *pa, char *pb);

int main(int argc, char const *argv[])
{
    char arr[100] = "hello world";
    char brr[100] = "nihao";
    twofist(arr, brr);
    //fistfun(arr,brr);
    printf("%s", arr);

    return 0;
}
//我的strcat
char *twofist(char *pa, char *pb)
{
    while (*pa)
    {
        pa++;
    }
    while (*pb)
    {
        *pa = *pb;
        pa++;
        pb++;
    }
    *pa = '\0';
    return pa;
}
//我的strcpy
char *fistfun(char *pa, char *pb)
{
    while (*pb)
    {
        *pa = *pb;
        pa++;
        pb++;
    }
    *pa = '\0';
    return pa;
}
