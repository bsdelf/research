#include <iostream>
#include "scx/RunTimer.hpp"
using namespace std;
using namespace scx;

unsigned long long sum0(int a)
{
    if (a <= 1)
	return 1;
    else 
	return a + sum0(a-1);

}

unsigned long long sum1(int a)
{
    if (a > 1)
	return a + sum1(a-1);
    else 
	return 1;
}

unsigned long long sum2(int a, unsigned long long asc)
{
    if (a > 1)
	return sum2(a-1, asc+a);
    else
	return asc;
}

unsigned long long sum3(int a)
{
    unsigned long long sum = 0;
    for (int i = 1; i <= a; ++i)
    {
	sum += i;
    }
    return sum;
}

int main()
{
    RunTimer timer;

    const int a = 999999999;
    timer.Start();
    unsigned long long a0 = sum0(a);
    timer.Stop();
    cout << timer.DiffUS() << endl;

    timer.Start();
    unsigned long long a1 = sum1(a);
    timer.Stop();
    cout << timer.DiffUS() << endl;

    timer.Start();
    unsigned long long a2 = sum2(a, 1);
    timer.Stop();
    cout << timer.DiffUS() << endl;

    timer.Start();
    unsigned long long a3 = sum3(a);
    timer.Stop();
    cout << timer.DiffUS() << endl;

    cout << a0 << endl;
    cout << a1 << endl;
    cout << a2 << endl;
    cout << a3 << endl;

    return 0;
}
