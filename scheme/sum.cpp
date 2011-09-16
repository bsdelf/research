#include <iostream>
using namespace std;

int sum(int times, int asc = 0)
{
    if (times != 0)
	return sum(--times, asc+times);
    else 
	return asc;
}

int main()
{
    cout << sum(100) << endl;
    return 0;
}
