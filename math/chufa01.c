/**
C编程题：求1/n，如果是循环小数的,只输出第一个循环节

例子：输入7，则输出 1/7=0._142857_
输入6，则输出 1/6=0.1_6_

*/

#include <stdio.h>
#include <stdlib.h>

// 使用链表实现
struct node
{
    int beichushu, shang;
    struct node *next;
};

int main()
{
    int beichushu = 1, chushu, yushu;
    struct node *head, *p, *q;
    head = (struct node *)malloc(sizeof(struct node));
    p = head;
    printf("Chushu=?( >1 )");
    scanf("%d", &chushu);
    printf("1/%d=0.", chushu);
    while (beichushu)
    {
        /* 从链表头开始查找是否bai是循环节的开始 */
        q = head->next;
        while (q && (q->beichushu != beichushu)) {
            //printf(q->beichushu);
            q = q->next;
        }
        if (q)
            break;
        /* 如果q不空，说明找到，无需继续计算了 */
        else
        { /* 否则继续计算下一位小数 */
            p->next = (struct node *)malloc(sizeof(struct node));
            p = p->next;
            p->beichushu = beichushu;
            beichushu *= 10;
            p->shang = beichushu / chushu;
            p->next = NULL;
            beichushu %= chushu;
        }
    }
    p = head->next;
    while (p != q) /* 本循环输出非循环节部分 */
    {
        printf("%d", p->shang);
        p = p->next;
    }
    if (q)
    {                /* 如果q不空，说明其商是一无限循环小数，存在循环节 */
        printf("_"); /* 输出时循环节用 '_' 括起 */
        while (q)
        {
            printf("%d", q->shang);
            q = q->next;
        }
        printf("_");
    }
    printf("\n");
    //getch();
    return 1;
}
