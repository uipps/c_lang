// 自然对数 e计算  https://www.yulucn.com/question/508840881

#include <stdio.h>

const int N = 1000;

int main()
{
  int s = 1;
  int a[N];

  for (int n = N; n > 0; n--)
  {
    int r = s % n;
    s = s / n + 1;
    for (int i = 0; i < N; i++)
    {
      r = r * 10 + a[i];
      a[i] = r / n;
      r = r % n;
    }
    for (int i = N - 1; i > 0; i--)
    {
      a[i - 1] = a[i - 1] + a[i] / 10;
      a[i] = a[i] % 10;
    }
    s += a[0] / 10;
    a[0] %= 10;
  }

  printf("%d", s);
  for (int i = 0; i < N; i++)
  {
    printf("%d", a[i]);
  }
  printf("\n");
  return 0;
}
