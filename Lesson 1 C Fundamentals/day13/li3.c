#include<stdio.h>
char * my_cpy(char *pa,char *pb)
{
    char *p=pa;
    while(*pb)
    {
        *pa=*pb;
        pa++;
        pb++;
    }
    *pa=*pb;
    return pa;
}
int main(int argc, char const *argv[])
{
    char h[15]="hello";
    char w[15]="world";
    my_cpy(h,w);
    printf("%s",h);
    return 0;
}
