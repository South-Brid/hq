//水仙花问题
#include<stdio.h>
#include<math.h>//-lm链接库函数
int main(int argc, char const *argv[])
{
    double x,y,z;
    for (int i = 100; i < 1000; i++)
    {
        x=i/100;//百位
        y=i/10%10;//十位
        z=i%10;//个位
        if(pow(x,3)+pow(y,3)+pow(z,3)==i)
        {
            printf("%d  ",i);
        }
    }
    return 0;
}
