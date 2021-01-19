#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;

typedef struct DNode
{
    ElemType data;
    struct DNode *prior;
    struct DNode *next;
} DLinkList;
/*---建立双链表---*/

/*---头插法建表---*/
void CreateListF(DLinkList *L, ElemType a[], int n)
{
    DLinkList *s;
    int i;
    L = (DLinkList *)malloc(sizeof(DLinkList));
    L->prior = L->next = NULL;
    for (i = 0; i < n; i++)
    {
        s = (DLinkList *)malloc(sizeof(DLinkList));
        s->data = a[i];
        s->next = L->next;
        if (L->next != NULL)
        {
            L->next->prior = s;
        }
        L->next = s;
        s->prior = L;
    }
}
/*---尾插法建表---*/
void CreateListR(DLinkList *L, ElemType a[], int n)
{
    DLinkList *s, *r;
    int i;
    L = (DLinkList *)malloc(sizeof(DLinkList));
    r = L;
    for (i = 0; i < n; i++)
    {
        s = (DLinkList *)malloc(sizeof(DLinkList));
        s->data = a[i];
        r->next = s;
        s->prior = r;
        r = s;
    }
    r->next = NULL;
}

/*---在双链表L中第i个位置上插入值为e的节点*/
bool ListInsert(DLinkList *L, int i, ElemType e)
{
    int j = 0;
    DLinkList *p = L, *s;
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
        s = (DLinkList *)malloc(sizeof(DLinkList));
        s->data = e;
        s->next = p->next;
        if (p->next != NULL)
        {
            p->next->prior = s;
        }
        s->prior = p;
        p->next = s;
        return true;
    }
}
/*---在双链表L删除第i个节点---*/
bool ListDelete(DLinkList *L, int i, ElemType e)
{
    int j = 0;
    DLinkList *p = L, *q;
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
        if (p->next != NULL)
        {
            p->next->prior = p;
        }
        free(q);
        return true;
    }
}
int main()
{
    return 0;
}