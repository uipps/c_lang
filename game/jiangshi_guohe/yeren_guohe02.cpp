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
4.2.2单函递归法

依次输入：
3
2

*/

#include <iostream>
using namespace std;

#define MAX 1024

typedef struct rule
{
    int missionary;
    int savage;
} Rule;

typedef struct node
{
    int missionary;
    int savage;
    int boat;
    int direct;
} Node;

typedef struct sequenceStack
{
    Node data[MAX];
    int top;
} SequenceStack;

int NUM = 0;

bool stack_empty(SequenceStack &stack)
{
    if (stack.top == -1)
    {
        return true;
    }
    return false;
}

bool stack_full(SequenceStack &stack)
{
    if (stack.top == MAX - 1)
    {
        return true;
    }
    return false;
}

bool stack_push(SequenceStack &stack, Node &node)
{
    if (stack_full(stack))
    {
        cout << "The stack is full,pushing failed!" << endl;
        return false;
    }
    stack.top++;
    stack.data[stack.top].missionary = node.missionary;
    stack.data[stack.top].savage = node.savage;
    stack.data[stack.top].boat = node.boat;
    stack.data[stack.top].direct = node.direct;
    return true;
}

bool stack_pop(SequenceStack &stack)
{
    if (stack_empty(stack))
    {
        cout << "The stack is empty,poping failed!" << endl;
        return false;
    }
    stack.top--;
    return true;
}

bool node_reach(Node &node)
{
    if (node.missionary == 0 && node.savage == 0 && node.boat == 0)
    {
        return true;
    }
    return false;
}

bool node_equal(Node &node1, Node &node2)
{
    if (node1.missionary == node2.missionary &&
        node1.savage == node2.savage &&
        node1.boat == node2.boat)
    {
        return true;
    }
    return false;
}

bool node_visited(SequenceStack &stack, Node &node)
{
    int ii;
    for (ii = 0; ii <= stack.top; ii++)
    {
        if (node_equal(stack.data[ii], node))
        {
            return true;
        }
    }
    return false;
}

void stack_print(SequenceStack &stack)
{
    int ii;
    cout << "The " << ++NUM << "st method is:" << endl;
    for (ii = 0; ii <= stack.top; ii++)
    {
        cout << "(" << stack.data[ii].missionary;
        cout << "," << stack.data[ii].savage;
        cout << "," << stack.data[ii].boat << ")" << endl;
    }
    cout << endl;
    system("pause");
}

void rule_print(int ruleset_num, Rule *rule)
{
    int ii;
    for (ii = 0; ii < ruleset_num; ii++)
    {
        cout << "(" << rule[ii].missionary << "," << rule[ii].savage << ")" << endl;
    }
    cout << endl;
    system("pause");
}

void rule_set(int &sample, int &capacity, Rule *rule)
{
    int ii, ij, ik = 0;
    for (ii = 0; ii < sample; ii++)
    {
        for (ij = 0; ij < sample; ij++)
        {
            if (ii == 0 && ij == 0)
            {
                continue;
            }
            if (ii + ij <= capacity)
            {
                rule[ik].missionary = ii;
                rule[ik++].savage = ij;
            }
        }
    }
}

int ruleset_num_get(int &sample, int &capacity)
{
    int ii, ij, num = 0;
    for (ii = 0; ii < sample; ii++)
    {
        for (ij = 0; ij < sample; ij++)
        {
            if (ii == 0 && ij == 0)
            {
                continue;
            }
            if (ii + ij <= capacity)
            {
                num++;
            }
        }
    }
    return num;
}

void init(SequenceStack &stack, int &ruleset_num, int &sample, int &capacity)
{
    cout << "Please enter the initial number of savages and missionaries:" << endl;
    cin >> sample;
    cout << "Please enter the ship's carrying capacity:" << endl;
    cin >> capacity;
    ruleset_num = ruleset_num_get(sample, capacity);
    cout << "\nThere is a total of " << ruleset_num << " sets of rules:" << endl;
    stack.top = 0;
    stack.data[stack.top].missionary = sample;
    stack.data[stack.top].savage = sample;
    stack.data[stack.top].boat = 1;
    stack.data[stack.top].direct = 0;
}

void processing(SequenceStack &stack, Rule *rule, int &ruleset_num, int &sample)
{
    Node cNode;
    if (node_reach(stack.data[stack.top]))
    {
        stack_print(stack);
    }
    else
    {
        while (stack.data[stack.top].direct < ruleset_num)
        {
            if (stack.data[stack.top].boat == 1)
            {
                cNode.missionary = stack.data[stack.top].missionary -
                                   rule[stack.data[stack.top].direct].missionary;
                cNode.savage = stack.data[stack.top].savage -
                               rule[stack.data[stack.top].direct].savage;
                cNode.boat = 0;
                cNode.direct = 0;
                if (node_visited(stack, cNode) == false &&
                    (cNode.missionary == cNode.savage ||
                     cNode.missionary == 0 || cNode.missionary == sample) &&
                    (cNode.missionary >= 0) && (cNode.missionary <= sample) &&
                    (cNode.savage >= 0) && (cNode.savage <= sample))
                {
                    stack_push(stack, cNode);
                    processing(stack, rule, ruleset_num, sample);
                    stack_pop(stack);
                }
            }
            else
            {
                cNode.missionary = stack.data[stack.top].missionary +
                                   rule[stack.data[stack.top].direct].missionary;
                cNode.savage = stack.data[stack.top].savage +
                               rule[stack.data[stack.top].direct].savage;
                cNode.boat = 1;
                cNode.direct = 0;
                if (node_visited(stack, cNode) == false &&
                    (cNode.missionary == cNode.savage ||
                     cNode.missionary == 0 || cNode.missionary == sample) &&
                    (cNode.missionary >= 0) && (cNode.missionary <= sample) &&
                    (cNode.savage >= 0) && (cNode.savage <= sample))
                {
                    stack_push(stack, cNode);
                    processing(stack, rule, ruleset_num, sample);
                    stack_pop(stack);
                }
            }
            stack.data[stack.top].direct++;
        }
    }
}

int main(int argc, char **argv)
{
    SequenceStack stack;
    Rule *rule;
    int ruleset_num, sample, capacity;
    init(stack, ruleset_num, sample, capacity);
    rule = new Rule[ruleset_num];
    rule_set(sample, capacity, rule);
    rule_print(ruleset_num, rule);
    processing(stack, rule, ruleset_num, sample);
    system("pause");
    return 0;
}