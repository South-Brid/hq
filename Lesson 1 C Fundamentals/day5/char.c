#include<stdio.h>
int main(int argc, char const *argv[])
{
    char arr[]={'a','b','c'};
    char brr[]="abc";
    int n=0;
    printf("%s\n",arr);
    printf("%s\n",brr);
    printf("%d\n",sizeof(arr)/sizeof(arr[0]));
    printf("%d\n",sizeof(brr)/sizeof(brr[0]));
    return 0;
}
