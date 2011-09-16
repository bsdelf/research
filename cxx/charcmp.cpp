#include <iostream>
#include <string>
using namespace std;

int main(int argc, char** argv)
{
    char s1[] = "hello";
    char s2[] = "hellO";
    string s3 = "hello";

    cout << sizeof(s1) << endl;
    cout << (string(s1) == s2 ? "==" : "<>") << endl;
    cout << (s1 == s3 ? "==" : "<>") << endl;

    return 0;
}
