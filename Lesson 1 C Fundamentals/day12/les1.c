#include<stdio.h>
#include<string.h>
int main(int argc, char const *argv[])
{
    char arr[]="Computer Science";
    int x =strlen(arr);
    char *pa=arr;
    int i;
    for ( i = 0; i < x; i=i+2)
    {
        printf("%c",pa[i]);
        printf("%d\n",i);
    }
    return 0;
}
