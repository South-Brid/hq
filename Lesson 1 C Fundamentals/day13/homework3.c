#include <stdio.h>
void exchang(int *pa, int *pb)
//局部变量只在当前函数体内有效
{
#if 0
    int t;
    t=*pa;
    *pa=*pb;
    *pb=t;
#endif
    *pa = *pa + *pb;
    *pb = *pa - *pb;
    *pa = *pa - *pb;
   
}
int main(int argc, char const *argv[])
{
    int num1, num2;
    puts("请输入num1和num2的值：");
    scanf("%d %d", &num1, &num2);
    exchang(&num1, &num2);
    printf("交换后num1:%d num2:%d\n", num1, num2);
    return 0;
}
