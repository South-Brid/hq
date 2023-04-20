//笔试题
//测试大小端口得方式
union un {
    int a;
    char b;
    short c;
};

#include <stdio.h>
int main(int argc, char const *argv[])
{
    //指针法
    int val = 0x12345678;//12是高字节 78是低字节
    char *p = (char *)&val;
    printf("%#x  %#x\n", *p, *(p + 1));
    //
    printf("%#x %#x\n", (char)val, (short)val);
    //共用体
    union un test;
    test.a = 0x12345678;
    printf("%#x %#x\n", test.b, test.c);
    return 0;
}
//高地址存放高字节，是小端