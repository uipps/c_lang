/**
参考： https://blog.csdn.net/csy981848153/article/details/7604440

绘制余弦曲线和直线, 

题目：在屏幕上显示0~360度的cos(x)曲线与直线f(x)=45*(y-1)+31的迭加图形。
其中cos(x)图形用“*”表示，f(x)用“+”表示，在两个图形相交的点上则用f(x)图形的符号。

*/
#include <stdio.h>
#include <math.h>

int main(void)
{
    double y;
    int x, m, n, yy;
    for (yy = 0; yy <= 20; yy++)
    {
        y = yy * 0.1;
        m = acos(1 - y) * 10;
        n = 45 * (y - 1) + 31;
        for (x = 0; x <= 62; x++)
        {
            if (x == m && x == n) //相交处
            {
                printf("+");
            }
            else if (x == n) //未相交处，直线
            {
                //cout << "+";
                printf("+");
            }
            else if (x == m || x == 62 - m) //未相交处，曲线
            {
                // cout << "*";
                printf("*");
            }
            else
                printf(" ");
            //cout << " ";
        }
        //cout << endl;
    }

    return 0;
}