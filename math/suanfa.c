// 计算2开平方（根号2）的计算方法
//  main调用sqrt计算2的算术平方根。更通用的算法只要更改一下main即可。这里的算法已经把原理解释的足够清楚。
//    本程序中，常数W表示数据的总位数，D标是小数部分位数。

#include <stdio.h>
#include <string.h>

const int W = 101;
const int D = 100;

int pos(int power)
{
  return power + D;
}

int power(int pos)
{
  return pos - D;
}

void fill(int d[W], int t)
{
  for (int i = 0; i < W; i++)
    d[i] = t;
}

void copy(int x[W], int y[W])
{
  for (int i = 0; i < W; i++)
    y[i] = x[i];
}

void assign(int x[W], char *n, char *d)
{
  fill(x, 0);
  char *p;
  p = n;
  int L = strlen(n);
  int i;
  for (i = L - 1; i >= 0; i--, p++)
    x[pos(i)] = *p - '0';
  L = strlen(d);
  p = d;
  for (i = -1; i >= -L; i--, p++)
    x[pos(i)] = *p - '0';
}

int equal(int x[W], int y[W])
{
  for (int i = W - 1; i > 0; i--)
    if (x[i] != y[i])
      return 0;
  return 1;
}

void mid(int x[W], int y[W], int z[W])
{
  z[0] = x[0] + y[0];
  for (int i = 1; i < W; i++)
  {
    z[i] = x[i] + y[i] + z[i - 1] / 10;
    z[i - 1] = z[i - 1] % 10;
  }
  int i = 0;
  for (i = W - 1; i > 0; i--)
  {
    z[i - 1] += (z[i] * 10) % 20;
    z[i] /= 2;
  }
  z[0] /= 2;
}

void sqr(int x[W], int y[W])
{
  fill(y, 0);
  int i = 0;
  for (i = 0; i < W; i++)
  {
    for (int j = 0; j < W; j++)
    {
      int t = pos(power(i) + power(j));
      if ((t >= 0) && (t < W))
        y[t] += x[i] * x[j];
    }
  }
  for (i = 0; i < W - 1; i++)
  {
    y[i + 1] += y[i] / 10;
    y[i] = y[i] % 10;
  }
  y[W - 1] = y[W - 1] % 10;
}

int compare(int x[W], int y[W])
{
  for (int i = W - 1; i >= 0; i--)
  {
    if (x[i] < y[i])
      return -1;
    if (x[i] > y[i])
      return 1;
  }
  return 0;
}

void print(int x[W])
{
  int i;
  for (i = W - 1; i >= 0; i--)
  {
    printf("%c", '0' + x[i]);
    if (i == D)
      printf(".");
  }
  printf("\n");
}

void sqrt2(int x[W], int y[W])
{
  int a[W], b[W], c[W];
  fill(a, 0);
  copy(x, b);
  b[pos(0)]++;
  while (!equal(a, b))
  {
    mid(a, b, c);
    sqr(c, y);
    if (compare(y, x) < 0)
      copy(c, a);
    else
      copy(c, b);
  }
  copy(c, y);
  return;
}

void main()
{
  int x[W], y[W];
  assign(x, "2", "0");
  sqrt2(x, y);
  print(y);
}