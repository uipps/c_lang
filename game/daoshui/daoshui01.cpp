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



// The following macros define the minimum required platform.  The minimum required platform
// is the earliest version of Windows, Internet Explorer etc. that has the necessary features to run
// your application.  The macros work by enabling all features available on platform versions up to and
// including the version specified.

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef _WIN32_WINNT        // Specifies that the minimum required platform is Windows Vista.
#define _WIN32_WINNT 0x0600 // Change this to the appropriate value to target other versions of Windows.
#endif

#include <stdio.h>
#include <deque>
#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>
#include <cassert>
using namespace std;
// TODO: reference additional headers your program requires here

// bucket_state.h :
//#define __BUCKET_STATE_H__
const int buckets_count = 3;
struct Action
{
    int from;
    int to;
    int water;
};
struct BucketState
{
    BucketState();
    BucketState(const int *buckets);
    BucketState(const BucketState& state);
    BucketState& operator=(const BucketState& state);
    bool IsSameState(const BucketState& state) const;
    void SetAction(int w, int f, int t);
    void SetBuckets(const int *buckets);
    void GetBuckets(int *buckets) const;
    bool IsBucketEmpty(int bucket);
    bool IsBucketFull(int bucket);
    void PrintStates();
    bool IsFinalState();
    bool DumpWater(int from, int to, BucketState& next);

    int bucket_s[buckets_count];
    Action curAction;
};


// bucket_state.cpp : 
int bucket_capicity[buckets_count] = {8, 5, 3};
int bucket_init_state[buckets_count] = {8, 0, 0};
int bucket_final_state[buckets_count] = {4, 4, 0};

void CopyStateArray(const int *from, int *to, int count)
{
    for (int i = 0; i < count; ++i)
    {
        to[i] = from[i];
    }
}

BucketState::BucketState()
{
    SetBuckets(bucket_init_state);
    SetAction(8, -1, 0);
}

BucketState::BucketState(const int *buckets)
{
    SetBuckets(buckets);
    SetAction(8, -1, 0);
}

BucketState::BucketState(const BucketState& state)
{
    SetBuckets((const int *)state.bucket_s);
    SetAction(state.curAction.water, state.curAction.from, state.curAction.to);
}

BucketState& BucketState::operator=(const BucketState& state)
{
    SetBuckets((const int *)state.bucket_s);
    SetAction(state.curAction.water, state.curAction.from, state.curAction.to);
    return *this;
}

bool BucketState::IsSameState(const BucketState& state) const
{
    for (int i = 0; i < buckets_count; ++i)
    {
        if (bucket_s[i] != state.bucket_s[i])
            return false;
    }

    return true;
}

void BucketState::SetAction(int w, int f, int t)
{
    curAction.water = w;
    curAction.from = f;
    curAction.to = t;
}

void BucketState::SetBuckets(const int *buckets)
{
    CopyStateArray(buckets, (int *)bucket_s, buckets_count);
}

void BucketState::GetBuckets(int *buckets) const
{
    CopyStateArray((const int *)bucket_s, buckets, buckets_count);
}

bool BucketState::IsBucketEmpty(int bucket)
{
    assert((bucket >= 0) && (bucket < buckets_count));

    return (bucket_s[bucket] == 0);
}

bool BucketState::IsBucketFull(int bucket)
{
    assert((bucket >= 0) && (bucket < buckets_count));

    return (bucket_s[bucket] >= bucket_capicity[bucket]);
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

bool BucketState::IsFinalState()
{
    return IsSameState(BucketState(bucket_final_state));
}

/*从'b4?from到'b5?to倒'b5?水'cb?，'a3?返'b7?回'bb?实'ca?际'bc?倒'b5?水'cb?体'cc?积'bb?*/
bool BucketState::DumpWater(int from, int to, BucketState& next)
{
    int bucket_water[buckets_count] = {0};

    GetBuckets(bucket_water);
    int dump_water = bucket_capicity[to] - bucket_water[to];
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
    if (dump_water > 0) /*是'ca?一'd2?个'b8?有'd3?效'd0?的'b5?倒'b5?水'cb?动'b6?作'd7??*/
    {
        next.SetBuckets(bucket_water);
        next.SetAction(dump_water, from, to);
    }
    return (dump_water > 0);
}
// end bucket_state.cpp



bool IsSameBucketState(BucketState state1, BucketState state2)
{
    return state1.IsSameState(state2);
}

bool IsProcessedState(deque<BucketState> &states, const BucketState &newState)
{
    deque<BucketState>::iterator it = states.end();

    it = find_if(states.begin(), states.end(),
                 bind2nd(ptr_fun(IsSameBucketState), newState));

    return (it != states.end());
}

void PrintResult(deque<BucketState> &states)
{
    cout << "Find Result : " << endl;
    for_each(states.begin(), states.end(),
             mem_fun_ref(&BucketState::PrintStates));
    cout << endl
         << endl;
}

bool IsCurrentActionValid(BucketState &current, int from, int to)
{
    /*不'b2?是'ca?同'cd?一'd2?个'b8?桶'cd?，'a3?且'c7?from桶'cd?中'd6?有'd3?水'cb?，'a3?且'c7?to桶'cd?中'd6?不'b2?满'c2?*/
    if ((from != to) && !current.IsBucketEmpty(from) && !current.IsBucketFull(to))
    {
        return true;
    }

    return false;
}

void SearchState(deque<BucketState> &states);

void SearchStateOnAction(deque<BucketState> &states, BucketState &current, int from, int to)
{
    if (IsCurrentActionValid(current, from, to))
    {
        BucketState next;
        /*从'b4?from到'b5?to倒'b5?水'cb?，'a3?如'c8?果'b9?成'b3?功'b9?，'a3?返'b7?回'bb?倒'b5?水'cb?后'ba?的'b5?状'd7?态'cc?*/
        bool bDump = current.DumpWater(from, to, next);
        if (bDump && !IsProcessedState(states, next))
        {
            states.push_back(next);
            SearchState(states);
            states.pop_back();
        }
    }
}

void SearchState(deque<BucketState> &states)
{
    BucketState current = states.back(); /*每'c3?次'b4?都'b6?从'b4?当'b5?前'c7?状'd7?态'cc?开'bf?始'ca?*/
    if (current.IsFinalState())
    {
        PrintResult(states);
        return;
    }

    /*使'ca?用'd3?两'c1?重'd6?循'd1?环'bb?排'c5?列'c1?组'd7?合'ba?种'd6?倒'b5?水'cb?状'd7?态'cc?*/
    for (int j = 0; j < buckets_count; ++j)
    {
        for (int i = 0; i < buckets_count; ++i)
        {
            SearchStateOnAction(states, current, i, j);
        }
    }
}

int main(int argc, char *argv[])
{
    deque<BucketState> states;
    BucketState init;

    states.push_back(init);
    SearchState(states);

    assert(states.size() == 1); /*穷'c7?举'be?结'bd?束'ca?后'ba?states应'd3?该'b8?还'bb?是'ca?只'd6?有'd3?一'd2?个'b8?初'b3?始'ca?状'd7?态'cc?*/

    return 0;
}