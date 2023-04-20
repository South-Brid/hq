#include <stdio.h>
int mystrlen(char *pa);
int main(int argc, char const *argv[])
{
    char arr[50] = {};
    scanf("%[^\n]", arr);
    printf("\033[0m\033[1;36m%d\033[0m\n", mystrlen(arr));
    return 0;
}
int mystrlen(char *pa)
{
    int num = 0;
    while (*pa)
    {
        num++;
        pa++;
    }
    return num;
}