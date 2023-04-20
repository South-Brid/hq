#include <stdio.h>
int main(int argc, char const *argv[])
{
#if 0
    char arr[20] = {};
    scanf("%[^\n]", arr);
    printf("%s\n", arr);

    char brr[20] = {};
    scanf("%s", brr);
    printf("%s", brr);

    char crr[20] = {};
    scanf("%[^a]", crr);//%[^\n]
    printf("%s\n", crr);
    char crr[20] = {};
    scanf("%[^a]", crr); //%[^\n]类似通配符
    printf("%s\n", crr);
#endif
    char drr[20]={};
    gets(drr);
    printf("%s",drr);
    return 0;
}
