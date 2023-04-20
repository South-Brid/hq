#include <stdio.h>
int main(int argc, char const *argv[])
{
    int num_w, num_q, num_s, num_g;
    int num = 0;
    while (1)
    {
        scanf(" %d", &num);
        num_w = num / 10000;
        num_q = num / 1000 % 10;
        num_s = num / 10 % 10;
        num_g = num % 10;
        if (num == 0)
        {
            break;
        }
        if (num_w == num_g && num_q == num_s)
        {
            printf("%d 为回文数\n", num);
        }
        else
        {
            puts("不是回文数");
        }
        
    }
    return 0;
}
