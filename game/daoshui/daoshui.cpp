/*
三只水桶等分水问题 ( https://blog.csdn.net/orbit/article/details/6596521 )
        有一个容积为8升的水桶里装满了水，另外还有一个容积为3升的空桶和一个容积为5升的空桶，如何利用这两个空桶等分8升水？附加条件是三个水桶都没有体积刻度，也不能使用其它辅助容器。
        这是一道经典题目，一般人都可以在一分钟内给出答案，不过，很多人可能没有注意到这道题的答案不是唯一的。先来看看最常见的一个答案，也是目前已知最快的操作步骤，共需要7次倒水动作：



二、 另外的方法： 一行代码搞定：
https://www.sohu.com/a/291640831_120087604
这道题其实是一道数学题，虽然据说微软的面试考过这道题。

数论中，有一个裴蜀定理（ Bézout's identity），说明了对任何整数x、y和它们的最大公约数d，一定存在整数a，b，使ax+by=d成立。

因此，只要满足z是GCD(x, y)的倍数，即可捣鼓出z升水。GCD(x, y)代表x，y的最大公约数。

所以，一行代码搞定！


*/

#include <iostream>

using namespace std;

//const int buckets_count 3;
//int buckets_count = 3;
#define buckets_count 3

struct Action
{

    int from;
    int to;
    int water;
};

struct BucketState
{
    int bucket_s[buckets_count]; /*状态向量*/
    Action curAction;            /*倒水动作*/
};

bool IsCurrentActionValid(BucketState &current, int from, int to)

{

    /*不是同一个桶，且from桶中有水，且to桶中不满*/

    if ((from != to)

        && !current.IsBucketEmpty(from)

        && !current.IsBucketFull(to))

    {

        return true;
    }

    return false;
}
void PrintResult(deque<BucketState> &states)

{

    cout << "Find Result : " << endl;

    for_each(states.begin(), states.end(),

             mem_fun_ref(&BucketState::PrintStates));

    cout << endl
         << endl;
}

void BucketState::PrintStates()

{

    cout << "Dump " << curAction.water << " water from "

         << curAction.from + 1 << " to " << curAction.to + 1 << ", ";

    cout << "buckets water states is : ";

    for (int i = 0; i < buckets_count; ++i)

    {

        cout << bucket_s[i] << " ";
    }

    cout << endl;
}

bool IsProcessedState(deque<BucketState> &states, BucketState &newState)

{

    deque<BucketState>::iterator it = states.end();

    it = find_if(states.begin(), states.end(),

                 bind2nd(ptr_fun(IsSameBucketState), newState));

    return (it != states.end());
}

void SearchState(deque<BucketState> &states)

{

    BucketState current = states.back(); /*每次都从当前状态开始*/

    if (current.IsFinalState())

    {

        PrintResult(states);

        return;
    }

    /*使用两重循环排列组合种倒水状态*/

    for (int j = 0; j < buckets_count; ++j)

    {

        for (int i = 0; i < buckets_count; ++i)

        {

            SearchStateOnAction(states, current, i, j);
        }
    }
}

void SearchStateOnAction(deque<BucketState> &states, BucketState &current, int from, int to)

{

    if (IsCurrentActionValid(current, from, to))

    {

        BucketState next;

        /*从from到to倒水，如果成功，返回倒水后的状态*/

        bool bDump = DumpWater(current, from, to, next);

        if (bDump && !IsProcessedState(states, next))

        {

            states.push_back(next);

            SearchState(states);

            states.pop_back();
        }
    }
}

bool DumpWater(const BucketState &current, int from, int to, BucketState &next)
{

    int bucket_water[buckets_count] = {0};

    current.GetBuckets(bucket_water);

    int dump_water = BucketState::bucket_dim[to] - bucket_water[to];

    if (bucket_water[from] >= dump_water)

    {

        bucket_water[to] += dump_water;

        bucket_water[from] -= dump_water;
    }

    else

    {

        bucket_water[to] += bucket_water[from];

        dump_water = bucket_water[from];

        bucket_water[from] = 0;
    }

    if (dump_water > 0) /*是一个有效的倒水动作?*/

    {

        next.SetBuckets(bucket_water);

        next.SetAction(dump_water, from, to);
    }

    return (dump_water > 0);
}

int main(void)
{

    return 0;
}
