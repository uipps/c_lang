#include <stdio.h>
void main()
{
    int data, i = 2;
    scanf("%d", &data);
    while (data > 1)
    {
        if (data % i == 0)
        {
            printf("%d ", i);
            data /= i;
        }
        else
            i++;
    }
}