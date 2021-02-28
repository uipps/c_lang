/*

有三个杯子容积如下：A:80L B:50L  C:30L
现在将A杯注满水，要达到如下状态(a:40  b:40  c:0)
应该如何操作？？？？

    参考： https://bbs.csdn.net/topics/70140283

*/

#include <iostream>

class Jug
{
public:
    int Set();
    void FillA();
    void FillB();
    void EmptyB();
    void EmptyA();
    void PourA_B();
    void PourB_A();
    int AFull();
    int BFull();
    int A_Pet();
    int B_Pet();
    int Test();

private:
    int A, B;
    int Ca, Cb;
    int N;
};
int Jug::Set()
{
    A = 0;
    B = 0;
    if (cin >> Ca >> Cb >> N)
        return 1;
    return 0;
}

void Jug::FillA()
{
    cout << "fill A" << endl;
    A = Ca;
}

void Jug::FillB()
{
    cout << "fill B" << endl;
    B = Cb;
}

void Jug::EmptyA()
{
    cout << "empty A" << endl;
    A = 0;
}

void Jug::EmptyB()
{
    cout << "empty B" << endl;
    B = 0;
}

void Jug::PourA_B()
{
    cout << "pour A B" << endl;
    if ((A + B) >= Cb)
    {
        A = A - (Cb - B);
        B = Cb;
    }
    else
    {
        B = A + B;
        A = 0;
    }
}

void Jug::PourB_A()
{
    cout << "pour B A" << endl;
    if ((B + A) >= Ca)
    {
        A = Ca;
        B = B - (Ca - A);
    }
    else
    {
        A = A + B;
        B = 0;
    }
}

int Jug::A_Pet()
{
    if (A == N)
        return 1;
    else
        return 0;
}

int Jug::B_Pet()
{
    if (B == N)
        return 1;
    else
        return 0;
}

int Jug::AFull()
{
    if (A == Ca)
        return 1;
    return 0;
}

int Jug::BFull()
{
    if (B == Cb)
        return 1;
    return 0;
}

int Jug::Test()
{
    if (N == Ca)
    {
        FillA();
        return 1;
    }
    if (N == Cb)
    {
        FillB();
        return 1;
    }
    return 0;
}

int main()
{
    Jug a;
    while (a.Set())
    {
        if (!a.Test())
            while (!a.A_Pet() && !a.B_Pet())
            {
                a.FillA();
                a.PourA_B();
                if (a.BFull())
                {
                    a.EmptyB();
                    a.PourA_B();
                }
            }
        cout << "success" << endl;
    }

    return 0;
}