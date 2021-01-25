/**
50.谁在说谎

题目：张三说李四在说谎，李四说王五在说谎，王五说张三和李四都在说谎。现在问：这三人中到底谁说的是真话，谁说的是假话？

参考： https://blog.csdn.net/csy981848153/article/details/7626784

*/

#include <stdio.h>

int main(void)
{
    int a, b, c;
    int tem = 0;

    for (a = 1; a >= 0; --a)
    {
        for (b = 1; b >= 0; --b)
        {
            for (c = 1; c >= 0; --c)
            {
                if ((a + b == 1) && (b + c == 1) && (a + b + c == 1))
                {
                    printf("张三%s\n", (1 == a ? "没说谎" : "说谎"));
                    printf("李四%s\n", (1 == b ? "没说谎" : "说谎"));
                    printf("王五%s\n", (1 == c ? "没说谎" : "说谎"));
                    tem = 1;
                }
            }
        }
    }

    if (0 == tem)
    {
        printf("三个人都说谎了！");
    }
    return 1;
}