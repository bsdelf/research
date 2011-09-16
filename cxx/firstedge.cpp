#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


bool first_lower(int a, int b)
{
    return a <= b;
}

bool first_upper(int a, int b)
{
    return a >= b;
}

int main()
{
    vector<int> list;
    list.resize(8);
    list[0] = 0;
    list[1] = 10;
    list[2] = 30;
    list[3] = 35;
    list[4] = 65;
    list[5] = 80;
    list[6] = 90;
    list[7] = 99;

    int array[] = {0, 10, 30, 35, 65, 80, 90, 99};

    //vector<int>::iterator iter = lower_bound(array, array+8, 31);
    int* iter = lower_bound(array, array+8, 31);

    //cout << (iter != list.begin() ? *--iter : *iter) << endl;
    cout << (iter != array ? *--iter : *iter) << endl;

    return 0;
}
