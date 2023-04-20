//猴子桃
#include <stdio.h>
int main(int argc, char const *argv[])
{
    int day=9,x1=0,x2=1;
    //共9天
    for(;day>0;day--)
    //倒推法
    {
        x1=2*(x2+1);
        x2=x1;
        
    }
    printf("桃子数量为%d\n",x1);

    return 0;
}
