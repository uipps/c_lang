
#include <stdio.h>
#include <math.h>

int main(void)
{
    /*此乃我自己的代码，不知道怎么搞的画出来是个菱形。
   double y;
   int x,n,r=10;
   for (y=10;y>=-10;y--)
   {
         x=sqrt(r*r-y*y)*2.5;
   for (n=0;n<abs(y);n++)
   {
    cout<<" ";
   }
   cout<<"*";
   for (;n<2*r-abs(y);n++)
   {
    cout<<" ";
   }
   cout<<"*";
   cout<<endl;
   }
   */
    //以下为官方标准答案，不清楚比例怎么调的
    double y;
    int x, m;
    for (y = 10; y >= -10; y--)
    {
        m = 2.5 * sqrt(100 - y * y); /*计算行y对应的列坐标m，2.5是屏幕纵横比调节系数因为屏幕的
        行距大于列距，不进行调节显示出来的将是椭圆*/
        for (x = 1; x < 30 - m; x++)
            printf(" "); /*图形左侧空白控制*/
        printf("*");     /*圆的左侧*/
        for (; x < 30 + m; x++)
            printf(" "); /*图形的空心部分控制*/
        printf("*\n");   /*圆的右侧*/
    }
    return 0;
}