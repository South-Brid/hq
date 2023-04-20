//计算空格个数
#include <stdio.h>
int main(int argc, char const *argv[])
{
    int add = 0;
    char arr[100] = "wadwd";
   // scanf("%[^\n]", arr); 
    gets(arr);
    for (int i = 0; i < 100; i++)
    {
        if (arr[i] == ' ')
        {
            add++;
        }
    }
    printf("%d\n", add);
    puts(arr);//返回值是字符的个数
    return 0;
}