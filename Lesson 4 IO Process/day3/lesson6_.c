#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 100

typedef struct student
{
    int number_stu;
    char name[10];
    int fenshu_stu;
} stu_t, *stu_p;
typedef struct school
{
    stu_t date[N];
    int last;
} sc_t, *sc_p;
//创建一个学校
sc_p CreatSchool();
//录入学生信息
sc_p InSchool(sc_p p);
//从高到底打印学生信息
void Printf(sc_p p);


int main(int argc, char const *argv[])
{
    sc_p p =CreatSchool();
    InSchool(p);
    InSchool(p);
    InSchool(p);
    Printf(p);

    return 0;
}

//创建一个学校
sc_p CreatSchool()
{
    sc_p p = (sc_p)malloc(sizeof(sc_t));
    if (p == NULL)
    {
        puts("malloc is error");
        return NULL;
    }
    p->last = -1;
    return p;
}
//录入学生信息
sc_p InSchool(sc_p p)
{
    int x;
    int y;
    char arr[10];
    puts("请输入详细信息：学号 姓名 成绩");
    scanf("%d %s %d", &x, arr, &y);
    p->last++;
    p->date[p->last].number_stu = x;
    strcpy(p->date[p->last].name, arr);
    p->date[p->last].fenshu_stu = y;
    return p;
}

//从高到底打印学生信息
void Printf(sc_p p)
{
    stu_t x;
    int i;
    int j;
    for (i = 0; i < p->last; i++)
    {
        for (j = 0; j < p->last - i; j++)
        {
            if (p->date[j].fenshu_stu > p->date[j + 1].fenshu_stu)
            {
                x=p->date[j];
                p->date[j]=p->date[j+1];
                p->date[j+1]=x;
            }
        }
    }
    int y;
    for (y = 0; y <= p->last; y++)
    {
        printf("%d %s %d \n",p->date[y].number_stu,p->date[y].name,p->date[y].fenshu_stu);
    }
}