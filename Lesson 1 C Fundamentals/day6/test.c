#include<stdio.h>
int main(int argc, char const *argv[])
{
    char arr[10]="hello";
    int x = sizeof(arr);
    printf("%s\n",arr);
    printf("%d\n",x);
    return 0;
}
