//打印9×9乘法表
#include<stdio.h>
int main(int argc, char const *argv[])
{
    for (int i = 1; i <10 ; i++)//行
    {
        for (int j = 1; j < i+1; j++)//列
        {
            int c =i*j;
            printf("%d*%d = %d ",i,j,c);
        }
        puts(" ");
    }
    
    return 0;
}
