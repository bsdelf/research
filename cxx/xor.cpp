#include <iostream>
using namespace std;

static inline void clear1(int& t)
{
    t = 0;
}

static inline void clear2(int& t)
{
    t &= ~t;
}

int main(int argc, char** argv)
{
    if (argc < 2)
	return -1;

    const size_t count = 99999999;
    int* data = new int[count];

    for (size_t i = 0; i < count; ++i)
    {
	data[i] = i;
    }
    
    typedef void (*PtrFn)(int&) ;
    PtrFn pfn;
    if (*argv[1] == 'x')
    {
	pfn = &clear2;
	cout << "using xor" << endl;
    }
    else 
    {
	pfn = &clear1;
	cout << "using set" << endl;
    }

    for (size_t i = 0; i < count; ++i)
    {
	pfn(data[i]);
    }

    delete[] data;

    return 0;
}
