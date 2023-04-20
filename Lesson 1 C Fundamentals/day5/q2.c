//q退出
#include<stdio.h>
int main(int argc, char const *argv[])
{
    char ch ;
    puts("please input char ");
    while (1)
    {
        scanf("%c",&ch);
        if (ch == '\n')
        continue;//利用continue删除/n
        if(ch == 'q')
            break;
        printf("%c\n",ch);
    }
    return 0;
}
