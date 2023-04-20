#include<stdio.h>
struct stu
{
    char a;
    double b;
};

int main(int argc, char const *argv[])
{
     struct stu a;
    printf("%d",sizeof(struct stu));
    return 0;
}
