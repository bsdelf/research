#include <iostream>
using namespace std;
#include "PacketInf.h"
#include <cstring>

class MsgHead: public PacketInf
{
public:
    int magic;
    int index;

public:
    void Read(char*& buffer)
    {
	BufferHelper::ReadVal(buffer, magic);
	BufferHelper::ReadVal(buffer, index);
    }

    void Write(char*& buffer) const
    {
	BufferHelper::WriteVal(buffer, magic);
	BufferHelper::WriteVal(buffer, index);
    }

    size_t Size() const
    {
	return 4 + 4;
    }

    void ToString() const
    {
	cout << "magic:" << magic << endl;
	cout << "index:" << index << endl;
    }
};

class MsgStudent: public PacketInf
{
public:
    string name;
    short age;

public:
    void Read(char*& buffer)
    {
	BufferHelper::ReadString(buffer, name);
	BufferHelper::ReadVal(buffer, age);
    }

    void Write(char*& buffer) const
    {
	BufferHelper::WriteString(buffer, name);
	BufferHelper::WriteVal(buffer, age);
    }

    size_t Size() const
    {
	return (4+name.size()) + 2;
    }
    
    void ToString() const
    {
	cout << "name:" << name << endl;
	cout << "age:" << age << endl;
    }
};

const int LOOP_COUNT = 9999;

int main()
{
    MsgHead head;
    head.magic = 100;
    head.index = 90;

    MsgStudent student;
    student.name = "hello world";
    student.age = 15;

    char* buffer;
    size_t bufferSize;
    PacketPtrVector v;

    v.push_back(&head);
    v.push_back(&student);
    bufferSize = PacketHelper::ToBuffer(v, buffer);

    /*
    MsgHead a;
    MsgStudent b;

    v.clear();
    v.push_back(&a);
    v.push_back(&b);
    PacketHelper::FromBuffer(v, buffer);

    cout << "size:" << bufferSize << endl;
    a.ToString();
    b.ToString();
    */

    for (int i = 0; i < LOOP_COUNT; ++i) 
    {

    }
    return 0;
}
