//代码优化
#include <stdio.h>
int main(int argc, char const *argv[])
{
    char arr[1000] = {};
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    int num4 = 0;
    scanf("%[^\n]",arr);
    for (int i = 0; i < strlen(arr); i++)//牛啊
    {
        if (arr[i] >= 'A' && arr[i] <= 'Z')
            num1++;
        if (arr[i] >= 'a' && arr[i] <= 'z')
            num2++;
        if (arr[i] >= 48 && arr[i] <=57 )
            num3++;
        if (arr[i] == ' ')
            num4++;
    }
    printf("大写字母数量=%d\n",num1);
    printf("小写字母数量=%d\n",num2);
    printf("数字数量=%d\n",num3);
    printf("空格数量=%d\n",num4);

    return 0;
}
