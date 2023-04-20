#include <stdio.h>
#include <string.h>
//宏定义
#define N 5

//函数说明
void babuf(int *, int);
void wan_num();
void trigle();
void dao_printf();
void find_number();
void new_babuf();
void chose();
void two_arr();
void two_brr();
void ju_num();

int main(int argc, char const *argv[])
{
#if 0
    int arr[] = {52, 44, 12, 11, 2, 5, 7, 6, 9, 7, 8, 100};
    int sz = sizeof(arr) / sizeof(int);
    babuf(arr, sz);
#endif
#if 0
    wan_num();
    trigle(); 
    dao_printf();
    find_number();
    new_babuf();
    chose();
    two_arr();
    two_brr();
#endif
    ju_num();
    return 0;
}

//函数定义区
//矩形阵
void ju_num()
{
    int arr[3][4] = {11,12,25,18,17,55,99,88,4,55,11,22};
    int i, j;
    // for (i = 0; i < 3; i++)
    // {
    //     for (j = 0; i < 4; i++)
    //     {
    //         scanf("%d", &arr[i][j]);
    //     }
    // }
    int x, y, h=0, l=0; //暂时存放思想
    //随机值问题
    for (x = 0; x < 3; x++)
    {
        for (y = 0; y < 4; y++)
        {

            if (arr[x][y] > arr[h][l])
            {
                h = x;
                l = y;
            }
        }
    }
    printf("%d %d %d",h+1,l+1,arr[h][l]);
}

//二维test
void two_brr()
{
    int arr[2][3] = {1, 2, 3, 4, 5, 6};
    printf("%p\n", arr);
    printf("%p\n", arr[0]);
    printf("%p\n", arr[0] + 1);
    printf("%p\n", arr[1]);
    printf("%p\n", arr[1] + 1);
}
//二维数组练习
void two_arr()
{
    int arr[2][3] = {{1, 2}, {5, 6}};
    int i;
    for (i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d", arr[i][j]);
        }
        puts("");
    }
}

//选择语句
void chose()
{
    int i, j, mid;
    int small;
    int arr[N] = {};
    for (i = 0; i < N; i++)
    {
        scanf("%d", &arr[i]); //注意
    }
    for (i = 0; i < N; i++)
    {
        small = i;
        for (j = i + 1; j < N; j++)
        {
            if (arr[j] < arr[small])
            {
                small = j;
            }
        }
        if (i != small)
        {
            mid = arr[i];
            arr[i] = arr[small];
            arr[small] = mid;
        }
    }
    for (i = 0; i < N; i++)
    {
        printf("%d ", arr[i]);
    }
}

//新冒泡
void new_babuf()
{
    int arr[N] = {};
    int i, j, mid;
    for (i = 0; i < N; i++)
    {
        scanf("%d", &arr[i]);
    }
    for (i = 0; i < N - 1; i++)
    {
        for (j = 0; j < N - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                mid = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = mid;
            }
        }
    }
    for (i = 0; i < N; i++)
    {
        printf("%d ", arr[i]);
    }
}

//计算大写字母，小写字符，空格，数量，代码的优化
void find_number()
{
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    int num4 = 0;
    char arr[100] = {};
    scanf("%[^\n]", arr);
    for (int i = 0; i < strlen(arr); i++) //注意
    {
        if (arr[i] >= 'A' && arr[i] <= 'Z')
            num1++;
        else if (arr[i] >= 'a' && arr[i] <= 'z')
            num2++;
        else if (arr[i] >= '0' && arr[i] <= '9')
            num3++;
        else if (arr[i] == ' ')
            num4++;
    }
    printf("big = %d\n", num1);
    printf("small = %d\n", num2);
    printf("nunmber = %d\n", num3);
    printf("kong = %d\n", num4);
}

//倒序打印
void dao_printf()

{
    int n;
    char arr[32] = "hello";
    char ch;
    int i;
    for (n = 0; arr[n] != '\0'; n++)
        ;
    for (i = 0; i < n / 2; i++)
    {
        ch = arr[i];
        arr[i] = arr[n - i - 1];
        arr[n - i - 1] = ch;
    }
    printf("%s ", arr);
}

//冒泡排序
void babuf(int *p, int num)
{
    int lun_num;
    int ci_num;
    int mid;
    for (lun_num = 0; lun_num < num - 1; lun_num++)
    {
        for (ci_num = 0; ci_num < num - lun_num - 1; ci_num++)
        {
            if (p[ci_num] > p[ci_num + 1])
            {
                mid = p[ci_num];
                p[ci_num] = p[ci_num + 1];
                p[ci_num + 1] = mid;
            }
        }
    }
    for (int i = 0; i < num; i++)
    {
        printf("%d ", p[i]);
    }
}

//查找完数
void wan_num()
{
    int chu_num;
    int add_num;
    for (chu_num = 1; chu_num < 1001; chu_num++)
    {
        add_num = 0;
        for (int bei_num = 1; bei_num < chu_num; bei_num++)
        {
            if (chu_num % bei_num == 0)
            {
                add_num += bei_num;
            }
        }
        if (add_num == chu_num)
        {
            printf("%d ", add_num);
        }
    }
}
//打印倒三角
void trigle()
{
    int num;
    scanf("%d", &num);
    for (int i_num = 0; i_num < num; i_num++)
    {
        for (int j_num = 0; j_num <= i_num; j_num++)
        {
            printf("*");
        }
        printf("\n");
    }
    for (int x_num = 0; x_num < num; x_num++)
    {
        for (int y_num = 0; y_num < x_num; y_num++)
        {
            printf(" ");
        }
        for (int i = num; i > x_num; i--)
        {
            printf("*");
        }
        printf("\n");
    }
}
