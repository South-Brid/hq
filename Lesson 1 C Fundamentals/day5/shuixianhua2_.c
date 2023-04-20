#include<stdio.h>
#include<math.h>//-lm链接库函数
int main(int argc, char const *argv[])
{
    double x,y,z;
    int i=100;
    while (i < 1000)
    {
        x=i/100;//百位
        y=i/10%10;//十位
        z=i%10;//个位
        if(pow(x,3)+pow(y,3)+pow(z,3)==i)
        {
            printf("%d  ",i);
        }
        i++;
    }
    return 0;
}
