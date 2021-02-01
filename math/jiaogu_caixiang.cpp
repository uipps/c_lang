/**
 * 角谷猜想
题目：日本一位中学生发现一个奇妙的“定理”，请角谷教授证明，而教授无能为力，于是产生角谷猜想。
猜想的内容是：任给一个自然数，若为偶数除以2，若为奇数则乘3加1，
得到一个新的自然数后按照上面的法则继续演算，若干次后得到的结果必然为1。请编程验证

https://blog.csdn.net/csy981848153/article/details/8118938

--
input the number:
13
times:1 after num*3+1:40
times:2 after num/2:20
times:3 after num/2:10
times:4 after num/2:5
times:5 after num*3+1:16
times:6 after num/2:8
times:7 after num/2:4
times:8 after num/2:2
times:9 after num/2:1
*/

#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    int num = 0;
    int count = 1;
    cout << "input the number:" << endl;
    cin >> num;

    do
    {
        if (num % 2 == 0) //偶数
        {
            num = num / 2;
            cout << "times:" << count << " after num/2:" << num << endl;
        }
        else //奇数
        {
            num = num * 3 + 1;
            cout << "times:" << count << " after num*3+1:" << num << endl;
        }
        count++;
    } while (num != 1);
    return 0;
}
