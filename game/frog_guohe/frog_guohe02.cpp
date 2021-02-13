//file name: frog.cpp
#include <iostream>
#include <array>
#include <deque>
#include <stdexcept>

using namespace std;
const int size = 7;
void GetPath(array<int, size> frog, deque<array<int, size>> path);
ostream &operator<<(ostream &output, deque<array<int, size>> &que);

int main()
{
    array<int, size> frog = {-1, -1, -1, 0, 1, 1, 1};
    deque<array<int, size>> path;
    path.push_back(frog);

    try {
        GetPath(frog, path);
    } catch (out_of_range) {
        cout << "out of range!" << endl;
    }

    return 0;
}

//求解青蛙过河的路径
void GetPath(array<int, size> frog, deque<array<int, size>> path) {
    int flag = 0;

    if (frog.at(0) == 1 && frog.at(1) == 1 && frog.at(2) == 1
        && frog.at(4) == -1 && frog.at(5) == -1 && frog.at(6) == -1) {
        cout << path;
        return;
    }

    for (int i = 0; i < size; ++i) {
        //右向的青蛙跳到邻近的空石头上
        if (i < size - 1 && frog.at(i) == -1 && frog.at(i + 1) == 0) {
            frog.at(i) = 0;
            frog.at(i + 1) = -1;
            flag = 1;
        }
        //右向的青蛙越过一只左向的青蛙跳到空石头上
        else if (i < size - 2 && frog.at(i) == -1 && frog.at(i + 1) == 1 && frog.at(i + 2) == 0) {
            frog.at(i) = 0;
            frog.at(i + 2) = -1;
            flag = 2;
        }
        //左向的青蛙跳到邻近的空石头上
        else if (i > 0 && frog.at(i) == 1 && frog.at(i - 1) == 0) {
            frog.at(i) = 0;
            frog.at(i - 1) = 1;
            flag = 3;
        }
        //左向的青蛙越过一只右向的青蛙跳到空石头上
        else if (i > 1 && frog.at(i) == 1 && frog.at(i - 1) == -1 && frog.at(i - 2) == 0) {
            frog.at(i) = 0;
            frog.at(i - 2) = 1;
            flag = 4;
        }

        if (flag) {
            path.push_back(frog);
            GetPath(frog, path);

            //复原青蛙的位置
            if (flag == 1) {
                frog.at(i) = -1;
                frog.at(i + 1) = 0;
            } else if (flag == 2) {
                frog.at(i) = -1;
                frog.at(i + 2) = 0;
            } else if (flag == 3) {
                frog.at(i) = 1;
                frog.at(i - 1) = 0;
            } else if (flag == 4) {
                frog.at(i) = 1;
                frog.at(i - 2) = 0;
            }
            flag = 0;
            path.pop_back();
        }
    }
}

//输出结果
ostream &operator<<(ostream &output, deque<array<int, size>> &que) {
    static int num;
    int count = 0;
    cout << "solution " << ++num << ':' << endl;

    for (deque<array<int, size>>::iterator iter = que.begin(); iter != que.end(); ++iter, ++count) {
        if (!count) {
            output << "    ";
        } else {
            output.width(2);
            output << count << ". ";
        }

        for (array<int, size>::const_iterator ptr = iter->begin(); ptr != iter->end(); ++ptr) {

            if (*ptr == -1) {
                output << "-> ";
            } else if (*ptr == 1) {
                output << "<- ";
            } else {
                output << "__  ";
            }
        }
        output << endl;
    }
    output << endl;
    return output;
}