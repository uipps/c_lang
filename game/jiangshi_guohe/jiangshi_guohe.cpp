/*
参考： https://blog.csdn.net/qq_42796107/article/details/85275646


*/
#include "stdio.h"
//#include "cstdlib.h"
#include "cstdlib"

#define MAX 100

struct gh
{
    int left_c;
    int left_yr;
    int boat_location;
};
struct gh gharr[MAX];
int index = 0;
int numpass = 0;
int start_c, start_yr;

int handle(gh t)
{
    if (t.left_c == 0 && t.left_yr == 0)
    {

        numpass++;
        printf("\n找到第%d条路径：\n", numpass);
        for (int i = 1; i <= index; i++)
        {
            printf("第%d次:", i);
            if (gharr[i].boat_location == 1)
                printf("右岸到左岸，");
            else
                printf("左岸到右岸，");
            printf("传教士过去%2d人，", abs(gharr[i].left_c - gharr[i - 1].left_c));
            printf("野人过去%2d人", abs(gharr[i].left_yr - gharr[i - 1].left_yr));
            printf("\n");
        }

        return 0;
    }

    for (int i = 0; i < index; i++)
    {
        if (t.left_c == gharr[i].left_c && t.left_yr == gharr[i].left_yr)
        {
            if (t.boat_location == gharr[i].boat_location)
            {
                return 0;
            }
        }
    }

    if (t.left_c < 0 || t.left_yr < 0 || t.left_c > start_c || t.left_yr > start_yr)
    {
        return 0;
    }

    if ((t.left_c < t.left_yr && t.left_c != 0) || (start_c - t.left_c < start_yr - t.left_yr && start_c - t.left_c != 0))
    {
        return 0;
    }

    struct gh tt;

    tt.left_c = t.left_c - 2 * t.boat_location;
    tt.left_yr = t.left_yr;
    tt.boat_location = (-t.boat_location);
    index = index + 1;
    gharr[index] = tt;
    handle(gharr[index]);
    index = index - 1;

    tt.left_c = t.left_c;
    tt.left_yr = t.left_yr - 2 * t.boat_location;
    tt.boat_location = (-t.boat_location);
    index = index + 1;
    gharr[index] = tt;
    handle(gharr[index]);
    index = index - 1;

    tt.left_c = t.left_c - 1 * t.boat_location;
    tt.left_yr = t.left_yr - 1 * t.boat_location;
    tt.boat_location = (-t.boat_location);
    index = index + 1;
    gharr[index] = tt;
    handle(gharr[index]);
    index = index - 1;

    tt.left_c = t.left_c - 1 * t.boat_location;
    tt.left_yr = t.left_yr;
    tt.boat_location = (-t.boat_location);
    index = index + 1;
    gharr[index] = tt;
    handle(gharr[index]);
    index = index - 1;

    tt.left_c = t.left_c;
    tt.left_yr = t.left_yr - 1 * t.boat_location;
    tt.boat_location = (-t.boat_location);
    index = index + 1;
    gharr[index] = tt;
    handle(gharr[index]);
    index = index - 1;
    return 0;
}

int main()
{
    printf("请输入初始传教士人数：");
    scanf("%d", &start_c);
    printf("请输入初始野人人数：");
    scanf("%d", &start_yr);
    gharr[index].left_c = start_c;
    gharr[index].left_yr = start_yr;
    gharr[index].boat_location = 1;
    handle(gharr[index]);
    if (numpass == 0)
        printf("不可能过河！\n");
    else
        printf("已为您找到%d条过河路径！并且已全部加载完毕！\n", numpass);
    return 0;
}