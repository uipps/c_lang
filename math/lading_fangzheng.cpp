/**
题目：构造 NXN 阶的拉丁方阵(2<=N<=9)，使方阵中的每一行和每一列中数字1到N只出现一次。

https://blog.csdn.net/csy981848153/article/details/7650086

--
1  2  3  4  5
2  3  4  5  1
3  4  5  1  2
4  5  1  2  3
5  1  2  3  4

*/

#include <iostream>
using namespace std;

int main(void)
{
    int num = 0;
    cout << "请输入拉丁方阵的阶数（范围2<=N<=9）：" << endl;
    cin >> num;
    if (num < 2 && num > 9)
    {
        cout << "阶数超过范围！" << endl;
    }

    for (int i = 0; i != num; ++i)
    {
        for (int j = 0; j != num; ++j)
        {
            cout << (i + j) % num + 1 << "  ";
        }
        cout << endl;
    }
    return 0;
}