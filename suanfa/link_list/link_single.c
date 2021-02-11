#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LinkList;

/*---建立单链表---*/

/*---头插法建表---*/
void CreateListF(LinkList *L, ElemType a[], int n)
{
    LinkList *s;
    int i;
    L = (LinkList *)malloc(sizeof(LinkList));
    L->next = NULL;
    for (i = 0; i < n; i++)
    {
        s = malloc(sizeof(LinkList));
        s->data = a[i];
        s->next = L->next;
        L->next = s;
    }
}
/*---尾插法建表---*/
void CreateListR(LinkList *L, ElemType a[], int n)
{
    LinkList *s, *r;
    int i;
    L = (LinkList *)malloc(sizeof(LinkList));
    r = L;
    for (i = 0; i < n; i++)
    {
        s = (LinkList *)malloc(sizeof(LinkList));
        s->data = a[i];
        r->next = s;
        r = s;
    }
    r->next = NULL;
}
/*---初始化线性表---*/
void InitList(LinkList *L)
{
    L = (LinkList *)malloc(sizeof(LinkList));
    L->next = NULL;
}
/*---注销线性表---*/
void DestroyList(LinkList *L)
{
    LinkList *pre = L, *p = L->next;
    while (p != NULL)
    {
        free(pre);
        pre = p;
        p = pre->next;
    }
    free(pre);
}
/*---线性表是否为空---*/
bool ListEmpty(LinkList *L)
{
    return (L->next == NULL);
}
/*---线性表的长度---*/
int ListLength(LinkList *L)
{
    int n = 0;
    LinkList *p = L;
    while (p->next != NULL)
    {
        n++;
        p = p->next;
    }
    return n;
}
/*---输出线性表---*/
void DispList(LinkList *L)
{
    LinkList *p = L->next;
    while (p != NULL)
    {
        printf("%d", p->next);
        p = p->next;
    }
    printf("\n");
}
/*---求线性表中某个数据元素值---*/
bool GetElem(LinkList *L, int i, ElemType e)
{
    int j = 0;
    LinkList *p = L;
    while (j < i && p != NULL)
    {
        j++;
        p = p->next;
    }
    if (p == NULL)
    {
        return false;
    }
    else
    {
        e = p->data;
        return true;
    }
}
/*---按元素值查找---*/
int LocateElem(LinkList *L, ElemType e)
{
    int i = 1;
    LinkList *p = L->next;
    while (p != NULL && p->data != e)
    {
        p = p->next;
        i++;
    }
    if (p == NULL)
    {
        return (0);
    }
    else
    {
        return (i);
    }
}
/*---插入数据元素---*/
bool ListInsert(LinkList *L, int i, ElemType e)
{
    int j = 0;
    LinkList *p = L, *s;
    while (j < i - 1 && p != NULL)
    {
        j++;
        p = p->next;
    }
    if (p == NULL)
    {
        return false;
    }
    else
    {
        s = (LinkList *)malloc(sizeof(LinkList));
        s->data = e;
        s->next = p->next;
        p->next = s;
        return true;
    }
}
/*---删除数据元素---*/
bool ListDelete(LinkList *L, int i, ElemType e)
{
    int j = 0;
    LinkList *p = L, *q;
    while (j < i - 1 && p != NULL)
    {
        j++;
        p = p->next;
    }
    if (p == NULL)
    {
        return false;
    }
    else
    {
        q = p->next;
        if (q == NULL)
        {
            return false;
        }
        e = q->data;
        p->next = q->next;
        free(q);
        return true;
    }
}
int main()
{
    return 0;
}