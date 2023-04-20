//pv操作函数
void PVfunc(struct sembuf *s, int semid, int num1, int op_num, int flag)
{
    s->sem_num = num1;
    s->sem_op = op_num;
    s->sem_flg = 0;
    semop(semid, s, flag); //最后一个是调用得灯得个数
}
//初始化封装函数
union sem_un Clear(int num, int val_num, int sem_post)
{

    static union sem_un sem;
    sem.val = val_num;
    semctl(num, sem_post, SETVAL, sem);
    return sem;
}

//遍历无头单向
void NoshowLink(link_p p)
{
    link_p pshow = p;
    while (pshow)
    {
        printf("%d ", p->data);
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
        pa = pb;
        pa = pa->next;
        pb->next = p->next;
        p->next = pb;
    }
}
