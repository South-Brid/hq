#include <stdio.h>
int main(int argc, char const *argv[])
{
    int date1, date2, sum;
    puts("请输入你的运算符号");
    int op = getchar();
    //printf("%d", op);
    puts("请输入你要计算的两个值");
    scanf("%d %d", &date1, &date2);
    switch (op)
    {
    case 42:
        sum = date1 * date2;
        printf("%d * %d = %d\n", date1, date2, sum);
        break;
    case 43:
        sum = date1 + date2;
        printf("%d + %d = %d\n", date1, date2, sum);
        break;
    case 45:
        sum = date1 - date2;
        printf("%d - %d = %d\n", date1, date2, sum);
        break;
    case 47:
        sum = date1 / date2;
        printf("%d / %d = %d\n", date1, date2, sum);
        break;
    default:
        break;
    }
    return 0;
}
