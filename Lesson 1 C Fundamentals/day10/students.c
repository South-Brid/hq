#include <stdio.h>
typedef struct students
{
    char name[55];
    int num;
    int class;
    int garde;
} STU;

int main(int argc, char const *argv[])
{
    STU new;
    puts("请依次输入姓名 学号 班级 分数");
    scanf("%s %d %d %d",
          new.name,
          &new.num,
          &new.class,
          &new.garde);
    printf("name:%s \nnum:%d \nclass:%d \ngarde:%d\n",
           new.name,
           new.num,
           new.class,
           new.garde);
    return 0;
}
