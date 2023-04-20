#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 100
typedef struct student
{
    int id;
    char name[32];
    float score;
} stu_t, *stu_q;

typedef struct
{
    stu_t date[N];
    int last;
} seqlist_t, *seqlist_p;

seqlist_p CreatLine();                               
int InsertPost(seqlist_p p, stu_t people, int post); 
void ShowPost(seqlist_p p);
int DeletePost(seqlist_p p, int post);

int main(int argc, char const *argv[])
{
    seqlist_p p = CreatLine();
    stu_t a = {1, "awei", 99};
    stu_t b = {2, "awei", 99};
    stu_t c = {3, "awei", 99};
    InsertPost(p, a, 0);
    InsertPost(p, b, 1);
    InsertPost(p, c, 2);
    DeletePost(p,0);
    ShowPost(p);
    return 0;
}
//遍历表
void ShowPost(seqlist_p p)
{
    for (int i = 0; i <= p->last; i++)
    {
        printf("%d %s %lf \n", p->date[i].id, p->date[i].name, p->date[i].score);
    }
}
//删除学生信息
int DeletePost(seqlist_p p, int post)
{
    if (p->last == -1)
    {
        puts("p is null");
        return -1;
    }
    if (post < 0 || post > p->last)
    {
        puts("post is error");
        return -1;
    }
    for (int i = post; i < p->last; i++)
    {
        p->date[i]=p->date[i+1];
    }
    p->last--;
    return 0;
}

//制定位置插入
int InsertPost(seqlist_p p, stu_t people, int post)
{
    if (p->last + 1 == N)
    {
        puts("p is full");
        return -1;
    }
    if (post < 0 || post > p->last + 1)
    {
        puts("post is error");
        return -1;
    }
    for (int i = p->last + 1; i > post; i--)
    {
        p->date[i] = p->date[i - 1];
    }
    p->date[post] = people;
    p->last++;
    return 0;
}
//创建
seqlist_p CreatLine()
{
    seqlist_p p = (seqlist_p)malloc(sizeof(seqlist_t));
    if (p == NULL)
    {
        puts("malloc is error");
        return NULL;
    }
    p->last = -1;
    return p;
}
