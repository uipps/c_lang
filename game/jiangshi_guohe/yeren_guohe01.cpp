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
4.2.1面向对象的迭代方法

*/

#include <iostream>
using namespace std;

typedef struct MCNode
{
    int m;
    int c;
    int b;
    int num;
    struct MCNode *next;
    struct MCNode *last;
} MCNode;

class List
{
private:
    MCNode *head;
    MCNode *rear;
    MCNode *current;

public:
    List();
    friend bool operator==(MCNode &node1, MCNode &node2);
    void push_front(MCNode cNode);
    void push_back(MCNode cNode);
    void pop_front();
    void pop_back();
    MCNode &front();
    MCNode &back();
    void print_list();
    bool hit_target(MCNode &cNode);
    bool legal(MCNode &cNode);
    bool empty();
    bool exist(MCNode &cNode);
};

List::List()
{
    head = new MCNode();
    rear = head;
    head->m = 3;
    head->c = 3;
    head->b = 1;
    head->num = 0;
    head->last = NULL;
    head->next = NULL;
}

bool operator==(MCNode &node1, MCNode &node2)
{
    if (node1.m == node2.m && node1.c == node2.c && node1.b == node2.b)
        return true;
    else
        return false;
}

void List::push_front(MCNode cNode)
{
    (*head).last = new MCNode();
    head->last->next = head;
    head = head->last;
    head->m = cNode.m;
    head->c = cNode.c;
    head->b = cNode.b;
    head->num = cNode.num;
    head->last = NULL;
}

void List::push_back(MCNode cNode)
{
    (*rear).next = new MCNode();
    rear->next->last = rear;
    rear = rear->next;
    rear->m = cNode.m;
    rear->c = cNode.c;
    rear->b = cNode.b;
    rear->num = cNode.num;
    rear->next = NULL;
}

void List::pop_front()
{
    if (head->next != NULL)
    {
        head = head->next;
        head->last = NULL;
    }
    else
    {
        head = NULL;
        rear = NULL;
    }
}

void List::pop_back()
{
    if (rear->last != NULL)
    {
        rear = rear->last;
        rear->next = NULL;
    }
    else
    {
        head = NULL;
        rear = NULL;
    }
}

MCNode &List::front()
{
    return *head;
}

MCNode &List::back()
{
    return *rear;
}

void List::print_list()
{
    MCNode current;
    current = *head;
    while (true)
    {
        cout << current.num << "," << current.m << "," << current.c << "," << current.b << endl;
        if (current.next == NULL)
            break;
        else
        {
            current.c = current.next->c;
            current.m = current.next->m;
            current.b = current.next->b;
            current.num = current.next->num;
            current.next = current.next->next;
        }
    }
    system("pause");
}

bool List::hit_target(MCNode &cNode)
{
    MCNode goalNode;
    goalNode.m = 0;
    goalNode.c = 0;
    goalNode.b = 0;
    if (cNode == goalNode)
        return true;
    else
        return false;
}

bool List::legal(MCNode &cNode)
{
    if (cNode.m >= 0 && cNode.m <= 3 && cNode.c >= 0 && cNode.c <= 3)
    {
        if ((cNode.m == cNode.c) || (cNode.m == 3) || (cNode.m == 0))
            return true;
        else
            return false;
    }
    else
        return false;
}

bool List::empty()
{
    if (head == NULL)
        return true;
    else
        return false;
}

bool List::exist(MCNode &cNode)
{
    MCNode *current;
    current = head;
    while (current != NULL)
    {
        if (cNode.b == current->b &&
            cNode.c == current->c && cNode.m == current->m)
            return true;
        else
            current = current->next;
    }
    return false;
}

void print(MCNode &cNode)
{
    cout << "节点输出：" << endl;
    cout << cNode.num << " " << cNode.m << "," << cNode.c << "," << cNode.b << endl;
    system("pause");
}

void expandNode(List &opend, List &closed)
{
    int ii;
    MCNode cNode = opend.front();
    MCNode node[5];
    if (cNode.b == 1)
    {
        for (ii = 0; ii < 5; ii++)
        {
            node[ii].b = 0;
        }
        node[0].m = cNode.m - 1;
        node[0].c = cNode.c;
        node[1].m = cNode.m;
        node[1].c = cNode.c - 1;
        node[2].m = cNode.m - 1;
        node[2].c = cNode.c - 1;
        node[3].m = cNode.m - 2;
        node[3].c = cNode.c;
        node[4].m = cNode.m;
        node[4].c = cNode.c - 2;
    }
    else
    {
        for (ii = 0; ii < 5; ii++)
        {
            node[ii].b = 1;
        }
        node[0].m = cNode.m + 1;
        node[0].c = cNode.c;
        node[1].m = cNode.m;
        node[1].c = cNode.c + 1;
        node[2].m = cNode.m + 1;
        node[2].c = cNode.c + 1;
        node[3].m = cNode.m + 2;
        node[3].c = cNode.c;
        node[4].m = cNode.m;
        node[4].c = cNode.c + 2;
    }
    for (ii = opend.front().num; ii != 5; ii++)
    {
        opend.front().num++;
        if (opend.legal(node[ii]) && !opend.exist(node[ii]))
        {
            opend.push_front(node[ii]);
            opend.front().num = 0;
            closed.push_back(opend.front());
            return;
        }
    }
}

void proceeding(List &opend, List &closed)
{
    int ii;
    int NUM = 0;
    while (!opend.empty())
    {
        //opend.print_list();
        if (opend.hit_target(opend.front()))
        {
            NUM++;
            cout << "The " << NUM << "st route is found!" << endl;
            closed.print_list();
            cout << endl;
            opend.pop_front();
            closed.pop_front();
        }
        else if (opend.front().num != 5)
        {
            expandNode(opend, closed);
        }
        else
        {
            opend.pop_front();
            closed.pop_back();
        }
    }
}

int main(int argc, char **argv)
{
    List opend, closed;
    proceeding(opend, closed);
    system("pause");
    return 0;
}
