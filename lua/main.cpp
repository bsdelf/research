#include <iostream>
#include <fstream>
using namespace std;

#include <cstring>
#pragma pack(push, 1)

struct Data
{
    char magic[3];
    int a;
    int b;
};

#pragma pack(pop)

int main()
{
    fstream stream;
    Data data;

    stream.open("hex", ios::in |ios::binary);
    stream.read((char*)&data, sizeof(data));
    stream.close();
    cout << string(data.magic, sizeof(data.magic)) << endl;
    cout << data.a << endl;
    cout << data.b << endl;


    memcpy(data.magic, "ELF", 3);
    data.a = 10;
    data.b = 100;

    stream.open("bin", ios::out | ios::binary);
    stream.write((char*)&data, sizeof(data));
    stream.close();

    return 0;
}
