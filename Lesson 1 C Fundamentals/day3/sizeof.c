#include<stdio.h>
int num2;
int main(int argc, char const *argv[])
{
    char a ='A';
    char b =65;

    char c ='\101';
    char d ='\x41';
    
    printf("%c\n",a);
    printf("%c\n",b);
    printf("%d\n",b);
    printf("%c\n",c);
    printf("%c\n",d);
    return 0;
}
