/*
野人传教士过河问题: 
    https://www.cnblogs.com/guanghe/p/5485800.html

1.问题重述
  在河的左岸有N个传教士、N个野人和一条船，传教士们想用这条船把所有人都运过河去，但有以下条件限制：

（1）修道士和野人都会划船，但船每次最多只能运K个人；
（2）在任何岸边野人数目都不能超过修道士，否则修道士会被野人吃掉。

假定野人会服从任何一种过河安排，请规划出一个确保修道士安全过河的计划。

2.问题分析
  2.1约束条件：
    ① M≧C 任何时刻两岸、船上都必须满足传教士人数不少于野人数（M=0时除外，既没有传教士） 
    ② M+C≦K 船上人数限制在K以内

  2.2求解：
    传教士与野人全部安全渡到对岸的解决方案

--
4.2.3双函递归法

*/
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 1024

typedef struct Rule
{
    int mm;
    int cc;
} Rule;
Rule rule[5] = {{1, 0}, {0, 1}, {1, 1}, {2, 0}, {0, 2}};

typedef struct Node
{
    int m;
    int c;
    int b;
} Node;

typedef Node elemtype;

typedef struct SequenStack
{
    elemtype data[MAXSIZE];
    int top;
} SequenStack;

int NUM = 0;

int visited(SequenStack *open, Node newnode)
{
    int ii = 0;
    if (open->top != -1)
    {
        for (ii = 0; ii != open->top; ii++)
        {
            if (newnode.m == open->data[ii].m &&
                newnode.c == open->data[ii].c &&
                newnode.b == open->data[ii].b)
            {
                return 1;
            }
        }
    }
    return 0;
}

int legal(SequenStack *open, Node newnode)
{
    int i = visited(open, newnode);
    if (i == 0)
    {
        if (newnode.m >= 0 && newnode.m <= 3 && newnode.c >= 0 && newnode.c <= 3)
        {
            if (newnode.m == 0 || newnode.m == 3 || newnode.m == newnode.c)
            {
                return 1;
            }
        }
    }
    return 0;
}

int Pop_SequenStack(SequenStack *S)
{
    if (S->top == -1)
    {
        printf("The linear list is empty,poping to stack failed！\n");
        return 0;
    }
    else
    {
        S->top--;
        return 1;
    }
}

int Push_SequenStack(SequenStack *S, Node node)
{
    if (S->top >= MAXSIZE - 1)
    {
        printf("The linear list is full,pushing to stack failed！\n");
        return 0;
    }
    S->top++;
    S->data[S->top] = node;
    return 1;
}

void print_result(SequenStack *open)
{
    int ii;
    printf("第%d种:\n", ++NUM);
    if (open->top != -1)
    {
        for (ii = 0; ii <= open->top; ii++)
        {
            printf("(%d,%d,%d)\n", open->data[ii].m,
                   open->data[ii].c, open->data[ii].b);
        }
    }
    printf("\n");
    system("pause");
}

void print(SequenStack *open)
{
    int ii;
    if (open->top != -1)
    {
        for (ii = 0; ii <= open->top; ii++)
        {
            printf("(%d,%d,%d)-->", open->data[ii].m,
                   open->data[ii].c, open->data[ii].b);
        }
    }
    printf("\n");
    system("pause");
}
void DFS(SequenStack *open, Node newnode);

void processing(SequenStack *open, Node newnode)
{
    int ii, flag;
    Node node;
    node.m = newnode.m;
    node.c = newnode.c;
    node.b = newnode.b;
    if (node.b == 1)
    {
        for (ii = 0; ii < 5; ii++)
        {
            node.m = newnode.m - rule[ii].mm;
            node.c = newnode.c - rule[ii].cc;
            node.b = 0;
            flag = legal(open, node);
            if (flag == 1)
            {
                Push_SequenStack(open, node);
                DFS(open, node);
                Pop_SequenStack(open);
            }
        }
    }
    else
    {
        for (ii = 0; ii < 5; ii++)
        {
            node.m = newnode.m + rule[ii].mm;
            node.c = newnode.c + rule[ii].cc;
            node.b = 1;
            flag = legal(open, node);
            if (flag == 1)
            {
                Push_SequenStack(open, node);
                DFS(open, node);
                Pop_SequenStack(open);
            }
        }
    }
}

void DFS(SequenStack *open, Node node)
{
    if (node.m == 0 && node.c == 0 && node.b == 0)
    {
        print_result(open);
    }
    else
    {
        processing(open, node);
    }
}

Node init_node()
{
    Node node;
    node.m = 3;
    node.c = 3;
    node.b = 1;
    return node;
}

SequenStack *Init_open()
{
    SequenStack *open;
    open = (SequenStack *)malloc(sizeof(SequenStack));
    open->top = -1;
    return open;
}

int main(int argc, char **argv)
{
    SequenStack *open = Init_open();
    Node node = init_node();
    Push_SequenStack(open, node);
    DFS(open, node);
    system("pause");
    return 0;
}