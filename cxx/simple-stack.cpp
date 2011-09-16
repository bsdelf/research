#include <iostream>
using namespace std;

#define push(pstack, data) (*pstack++ = data)
#define pop(pstack) (*--pstack)

int main()
{
    int stack[100];
    int* ps = stack;

    for (int i = 0; i < 10; ++i)
	push(ps, i);
    for (int i = 0; i < 10; ++i)
	cout << pop(ps) << ",";

    cout << endl;
}
