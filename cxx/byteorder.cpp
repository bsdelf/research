#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    int a = 0x12345678;
    char* p = (char*)&a;

    for (int i = 0; i < sizeof(a); ++i)
    {
	cout << hex << (int)p[i] << ", ";
    }

    cout << endl;

    
    const char ch[] = "ABCD";
    int b;
    memcpy(&b, ch, 4);
    cout << (char*)&b << endl;

    int c;
    c = 'ABCD';
    cout << string((char*)&c,4) << endl;

    return 0;
}

