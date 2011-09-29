#include <iostream>
using namespace std;
#include "PacketInf.h"
#include <cstring>
#include <sstream>
#include "scx/RunTimer.hpp"
#include "msghead.pb.h"
#include "message.h"
using namespace scx;

#pragma pack(push, 1)
struct SimpleHead
{
    int magic;
    unsigned long long index;
};
#pragma pack(pop)

class MsgHead: public PacketInf
{
public:
    int magic;
    unsigned long long index;

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
	return 4 + 8;
    }

    void ToString() const
    {
	cout << "magic:" << magic << "\tindex:" << index << endl;
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
    /*
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

    cout << "sizeof(SimpleHead):" << sizeof(SimpleHead) << endl;
    int bufferSize = LOOP_COUNT*sizeof(SimpleHead);
    char* pBuffer;
    RunTimer timer;

    char* buffer1 = new char[bufferSize];
    char* buffer2 = new char[bufferSize];

    timer.Start();
    pBuffer = buffer2;
    for (int i = 0; i < LOOP_COUNT; ++i) 
    {
	SimpleHead* head = (SimpleHead*)pBuffer;
	head->magic = (int)(1984+i);
	head->index = i;
	pBuffer += sizeof(SimpleHead);
    }
    timer.Stop();
    cout << "struct cast:" << timer.DiffUS() << '\t' << pBuffer - buffer2 << endl;

    timer.Start();
    pBuffer = buffer1;
    for (int i = 0; i < LOOP_COUNT; ++i)
    {
	MsgHead head;
	head.magic = (int)1984+i;
	head.index = i;
	head.Write(pBuffer);
    }
    timer.Stop();
    cout << "new msg:" << timer.DiffUS() << '\t' << pBuffer - buffer1 << endl;

    timer.Start();
    for (int i = 0; i < LOOP_COUNT; ++i)
    {
	Message message(0);
	message.appendField(covIntStr(i));
	message.encode();
    }
    timer.Stop();
    cout << "old message:" << timer.DiffUS() << endl;

    GOOGLE_PROTOBUF_VERIFY_VERSION;
    timer.Start();
    stringstream stream;
    global::Head head;
    pBuffer = buffer1;
    for (int i = 0; i < LOOP_COUNT; ++i)
    {
	head.set_magic(1984+i);
	head.set_index(i);
	head.SerializeToArray(pBuffer, head.ByteSize());
	pBuffer += head.ByteSize();
	    //SerializeToOstream(&stream);
    }
    timer.Stop();
    cout << "protobuf:" << timer.DiffUS() << endl;
    google::protobuf::ShutdownProtobufLibrary();
    cout << stream.str() << endl;

    pBuffer = buffer2;
    for (int i = 0; i < LOOP_COUNT; ++i)
    {
	MsgHead head;
	head.Read(pBuffer);
	//head.ToString();
    }
    delete[] buffer1;
    delete[] buffer2;

    return 0;
}
