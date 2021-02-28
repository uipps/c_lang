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
4.2.4类集框架迭代版

*/

#include <iostream>
#include <vector>
#include <list>
using namespace std;

typedef struct MCNode
{
    int m;
    int c;
    int b;
    int num;
} MCNode;

int NUM = 0;

bool operator==(MCNode &m1, MCNode &m2)
{
    if (m1.m == m2.m && m1.c == m2.c && m1.b == m2.b)
        return true;
    else
        return false;
}

bool goal(MCNode &cNode)
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

bool legal(MCNode &cNode)
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

bool visited(MCNode cNode, list<MCNode> &opend)
{
    list<MCNode>::iterator it;
    for (it = opend.begin(); it != opend.end(); it++)
    {
        if (it->m == cNode.m && it->c == cNode.c && it->b == cNode.b)
            return true;
    }
    return false;
}

void print_list(list<MCNode> &opend)
{
    list<MCNode>::iterator it;
    for (it = opend.begin(); it != opend.end(); it++)
    {
        cout << it->num << "," << it->m << "," << it->c << "," << it->b << endl;
    }
    system("pause");
}

void print_result(vector<MCNode> &closed)
{
    vector<MCNode>::iterator it;
    for (it = closed.begin(); it != closed.end(); it++)
    {
        cout << it->num << "," << it->m << "," << it->c << "," << it->b << endl;
    }
    cout << endl;
    system("pause");
}

void expandNode(list<MCNode> &opend, vector<MCNode> &closed)
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
        if (legal(node[ii]) && !visited(node[ii], opend))
        {
            opend.push_front(node[ii]);
            opend.front().num = 0;
            closed.push_back(opend.front());
            return;
        }
    }
}

void proceeding(list<MCNode> &opend, vector<MCNode> &closed)
{
    int ii;
    while (!opend.empty())
    {
        //print_list(opend);
        if (goal(opend.front()))
        {
            NUM++;
            cout << "The " << NUM << "st route is found!" << endl;
            print_result(closed);
            opend.pop_front();
            closed.pop_back();
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

MCNode initNode()
{
    MCNode cNode;
    cNode.m = 3;
    cNode.c = 3;
    cNode.b = 1;
    cNode.num = 0;
    return cNode;
}

int main(int argc, char **argv)
{
    list<MCNode> opend;
    vector<MCNode> closed;
    opend.push_front(initNode());
    proceeding(opend, closed);
    system("pause");
    return 0;
}