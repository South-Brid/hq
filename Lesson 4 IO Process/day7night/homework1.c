#include <stdlib.h>
#include <stdio.h>
typedef int datatype;
typedef struct node_t
{
    datatype data;
    struct node_t *next;
} link_t, *link_p;

//遍历无头单向
void NoshowLink(link_p p)
{
    link_p pshow = p;
    while (pshow)
    {
        printf("%d ", pshow->data);
        pshow = pshow->next;
    }
}

//遍历有头单项
void ShowLink(link_p p)
{
    link_p pshow = p;
    while (pshow->next)
    {
        pshow = pshow->next;
        printf("%d ", pshow->data);
    }
}
//链表倒置
void DaoZhiLink(link_p p)
{
    link_p pb = NULL;
    link_p pa = p->next;
    p->next = NULL;
    while (pa)
    {
        pb = pa;
        pa = pa->next;
        pb->next = p->next;
        p->next = pb;
    }
}

//链表长度计算
int LenLine(link_p p);
//链表插入数据
int InsertLine(link_p p, datatype value, int post);
//创建链表
link_p CreateLine();
//链表删除数据
int DeleteLine(link_p p, int post);
//遍历验证
void ShowLine(link_p p);

int main(int argc, char const *argv[])
{
    link_p p = CreateLine();
    InsertLine(p, 10, 0);
    InsertLine(p, 20, 1);
    InsertLine(p, 30, 2);
    InsertLine(p, 40, 3);
    // DaoZhiLink(p);
    // ShowLine(p);
    NoshowLink(p);
    //ShowLink(p);
    return 0;
}

//遍历验证
void ShowLine(link_p p)
{
    while (p->next)
    {
        printf("%d\n", p->next->data);
        p = p->next;
    }
}
//链表删除数据
int DeleteLine(link_p p, int post)
{
    link_p pdel = NULL;
    if (post < 0 || post >= LenLine(p))
    {
        printf("post is error");
        return -1;
    }
    for (int i = 0; i < post; i++)
    {
        p = p->next;
    }
    pdel = p->next;
    p->next = pdel->next;
    free(pdel);
    pdel = NULL;
    return -1;
}

//链表插入数据
int InsertLine(link_p p, datatype value, int post)
{
    if (post < 0 || post > LenLine(p))
    {
        printf("post is error");
        return -1;
    }
    link_p pnew = (link_p)malloc(sizeof(link_t));
    if (pnew == NULL)
    {
        printf("malloc pnew is error\n");
        return -1;
    }
    pnew->next = NULL;
    pnew->data = value;
    for (int i = 0; i < post; i++)
    {
        p = p->next;
    }
    pnew->next = p->next;
    p->next = pnew;
    return 0;
}
//链表长度计算
int LenLine(link_p p)
{
    int i = 0;
    while (p->next)
    {
        i++;
        p = p->next;
    }
    return i;
}

//创建链表
link_p CreateLine()
{
    link_p p = (link_p)malloc(sizeof(link_t));
    if (p == NULL)
    {
        printf("malloc p is error\n");
        return NULL;
    }
    p->next = NULL;
    p->data = 50;
    return p;
}