#include <stdio.h>
#define max 5
void print(int *pa);
int *choselist();
void tao();
void point_test();
void point_test2();
void point_test3();
void point_test4();
void point_test5();
void point_test6();
int add(int a,int b);

int main(int argc, char const *argv[])
{
#if 0
    print(choselist());
    tao();
    point_test();
    point_test2();
    point_test3();
    point_test4();
    point_test5();
    point_test5();
#endif
    printf("%d\n",add(1000,5));
    return 0;
}

//函数测试
int add(int a,int b)
{
    return a-b;
}
void point_test6()
{
    int a = 10;
    int b = 20;
    int c = 30;
    int *pa[3] = {&a, &b, &c};
    printf("%d\n", **(pa + 1));
}
//核心是p[i]==*(p+i)
void point_test5()
{
    char *p[3] = {"hello", "world", "hqyj"};
    printf("%s\n",*(p+1));
    printf("%c\n",*(*(p+1)+4));
    printf("%s\n",*(p+2));

}

//指针数组
void point_test4()
{
    int a[2][2] = {7, 8, 9, 10};
    int(*p)[2] = a;
    printf("%p %p %p\n", a, *a, *a + 1);
    printf("%p %p %p\n", p, *p, *p + 1);
}

//指针访问测试3
void point_test3()
{
    int a[2][2] = {9, 7, 5, 1};
    printf("%p\n", *a);
    printf("%p\n", *a + 1);
    printf("%p\n", *(a + 1));
    printf("%p\n", *(a + 1) + 1);
}

//指针访问测试2
void point_test2()
{
    int arr[5] = {7, 6, 5, 4, 3};
    int *p = arr;
    printf("%d\n", *p++);
    printf("%d\n", *p);
}
//指针访问测试
void point_test()
{
    int arr[5] = {7, 6, 5, 4, 3};
    int *p = arr;
    printf("%d\n", *(p + 1));
    printf("%d\n", p[0]);
    printf("%d\n", p[1]);
    printf("%d\n", p[2]);
}

//桃子
void tao()
{
    int arr[10] = {0};
    arr[9] = 1;
    int i, num = 0;
    for (i = 9; i > 0; i--)
    {
        arr[i - 1] = (arr[i] + 1) * 2;
    }
    printf("桃子数为%d ", arr[0]);
}

//打印
void print(int *pa)
{
    int i;
    for (i = 0; i < max; i++)
    {
        printf("%d ", pa[i]);
    }
}

//选择
int *choselist()
{
    static int arr[max] = {9, 5, 7, 3, 10};
    int i, j, k, z;
    for (i = 0; i < max - 1; i++)
    {
        k = i;
        for (j = i + 1; j < max; j++)
        {
            if (arr[j] < arr[k])
            {
                k = j;
            }
        }
        if (arr[k] != arr[i])
        {
            z = arr[k];
            arr[k] = arr[i];
            arr[i] = z;
        }
    }
    return arr;
}