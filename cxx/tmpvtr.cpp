#include <iostream>
#include <string>
#include "scx/RunTimer.hpp"
#include "scx/Function.hpp"
using namespace std;
using namespace scx;

class base
{
    public:
	virtual int opt(int a) = 0;
};

class add1: public base
{
    public:
	virtual int opt(int a)
	{
	    return a+a;
	}
};

class pow1: public base
{
    public:
	virtual int opt(int a)
	{
	    return a*a;
	}
};


class add2
{
    public:
	int opt(int a)
	{
	    return a+a;
	}
};

class pow2
{
    public:
	int opt(int a)
	{
	    return a*a;
	}
};

int add(int a)
{
    return a+a;
}

int pow(int a)
{
    return a*a;
}

int main()
{
    RunTimer t;
    const size_t count = 99999999;

    add1 a1; pow1 p1;
    add2 a2; pow2 p2;

    base* pb;

    pb = &a1;
    t.Start();
    for (size_t i = 0; i < count; ++i)
    {
	pb->opt(i);
    }
    t.Stop();
    cout << t.DiffMS() << endl;

    pb = &p1;
    t.Start();
    for (size_t i = 0; i < count; ++i)
    {
	pb->opt(i);
    }
    t.Stop();
    cout << t.DiffMS() << endl;

    typedef int (*fopt)(int);
    struct intf
    {
	fopt popt;
    } myintf;

    myintf.popt= &add;
    t.Start();
    for (size_t i = 0; i < count; ++i)
    {
	(*myintf.popt)(i);
    }
    t.Stop();
    cout << t.DiffMS() << endl;

    myintf.popt = &pow;
    t.Start();
    for (size_t i = 0; i < count; ++i)
    {
	(*myintf.popt)(i);
    }
    t.Stop();
    cout << t.DiffMS() << endl;

    return 0;
}
