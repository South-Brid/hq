#include <stdio.h>
int main(int argc, char const *argv[])
{
    printf("please input \n");
    int num1, num2;
    char op;
    scanf("%d %c %d", &num1, &op, &num2);
    switch (op)
    {
    case '+':
        printf("%d\n", num1 + num2);
        break;
    case '-':
        printf("%d\n", num1 - num2);
        break;
    case '*':
        printf("%d\n", num1 * num2);
        break;
    case '/':
        if (num2 == 0)
        {
            puts("erro");
        }
        printf("%d\n", num1 / num2);
        break;
    default:
        break;
    }
    return 0;
}
