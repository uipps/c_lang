// 高精度乘法
#include <iostream>
#include <string>
#define N 1000

using namespace std;
int main()
{
    char num1[N];
    char num2[N];
    int data1[N];
    int data2[N];
    int result[N * 2];
    memset(data1, 0, sizeof(data1));
    memset(data2, 0, sizeof(data2));
    // 注意初始化
    memset(result, 0, sizeof(result));
    cin >> num1;
    cin >> num2;
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    for (int i = 0; i < len1; i++)
        data1[i] = num1[len1 - 1 - i] - '0';
    for (int i = 0; i < len2; i++)
        data2[i] = num2[len2 - 1 - i] - '0';
    int carry = 0;
    for (int i = 0; i < len1; i++)
    {
        carry = 0;
        for (int j = 0; j < len2; j++)
        {
            // 重点: i + j
            result[i + j] += data1[i] * data2[j] + carry;
            carry = result[i + j] / 10;
            result[i + j] %= 10;
        }
        // 每一遍循环之后的进位
        result[i + len2] += carry;
    }
    int index = len1 + len2;
    // 去掉前面多余的0
    while (index > 0 && result[index] == 0)
        index--;
    for (int i = index; i >= 0; i--)
        cout << result[i];
    cout << endl;
    return 0;
}