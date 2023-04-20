#include <stdio.h>
int main(int argc, char const *argv[])
{
    char arr[100] = {};
    scanf("%[^\n]", arr);
    char *pa = arr;
    int num=0;
    while (*pa != '\0')
    {
        num=num*10+*pa-'0';
        pa++;
    }
    printf("%d\n",num);

    return 0;
}
