//q退出
#include<stdio.h>
int main(int argc, char const *argv[])
{
    puts("please input char ");
    while (1)
    {
        int ch = getchar();
        if(ch == 113)
            break;
        putchar(ch);
    }
    return 0;
}
