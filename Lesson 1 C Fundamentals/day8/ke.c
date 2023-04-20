#include <stdio.h>
#include <string.h>
void zhizhen_1();
void size_zhizhen();
void st_it();
void daozhi();
void bigsmall();
void hah();
void test1();
void tao();
void jiao();

int main(int argc, char const *argv[])
{
#if 0
    zhizhen_1();
    size_zhizhen();
    st_it();
    daozhi();
    bigsmall();
    hah();
    test1();\
    tao();
#endif
    jiao();
    return 0;
}

void zhizhen_1()
{
    int a = 5;
    int *p = &a;
    printf("&a = %p\n", &a);
    printf("p = %p\n", p);
    printf("*p = %p\n", &*p);
    printf("&p = %p\n", &p);
}

void size_zhizhen()
{
    int a = 0;
    int *p = &a;

    char ch = 'a';
    char *p1 = &ch;

    float b = 3.14;
    float *p2 = &b;

    printf("%d\n", sizeof(p));
    printf("%d\n", sizeof(p1));
    printf("%d\n", sizeof(p2));
}

//字符整形输出

void st_it()
{
    char s[10] = {};
    int i;
    scanf("%s", s);
    int num = 0;
    char *pa = s;
    while (*pa != '\0')
    {
        num = num * 10 + (*pa - '0');
        //核心代码
        pa++;
    }
    printf("%d", num);
}

void daozhi()
{
    char arr[32] = "hello";
    char ch;
    char *p1 = arr;
    char *p2 = p1 + strlen(arr) - 1;
    while (p2 > p1)
    {
        ch = *p1;
        *p1 = *p2;
        *p2 = ch;
        p2--;
        p1++;
    }
    printf("%s", arr);
}

void con()
{
    int a = 10;
    int b = 10;
    // const int* p=&a;
    //  p=&b;
    // *p=20;
    int *p = &a;
    p = &b;
    *p = 20;
}

//大小端测试
void bigsmall()
{
    int a = 0x12345678;
    char b;
    b = (char)a;
    printf("%#x\n", b);
}

//测试a+i
void hah()
{
    int a[5] = {8, 5, 2, 3, 1};
    int i;
    for (i = 0; i < 5; i++)
    {
        printf("%d ", *(a + i));
        printf("%p ", a + i);
        puts("");
        printf("%d ", a[i]);
        printf("%p ", &a[i]);
        puts("");
    }
}

//课上习题1
void test1()
{
    char str[100] = "he";
    scanf("%s", str);
    char *pa = str;
    int num = 0;
    while (*pa)
    {
        num = num * 10 + num - 48; //重点
        pa++;
    }
    printf("%s", str);
}

//桃
void tao()
{
    int arr[10] = {0};
    arr[9] = 1;
    int i;
    for (i = 9; i > 0; i--)
    {
        arr[i - 1] = (arr[i] + 1) * 2;
    }
    printf("%d", arr[0]);
}

//三角
void jiao()
{
    int arr[10][10] = {0};
    int i, j, k;
    for (i = 0; i < 10; i++)
    {
        arr[i][0] = 1;
        for (j = 1; j <= i; j++)
        {
            arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
        }

        puts(" ");
    }
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j <= i; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
}
