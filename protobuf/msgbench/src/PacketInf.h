#ifndef PACKETINF_H
#define PACKETINF_H

#include <vector>
using namespace std;

class PacketInf
{
public:
    virtual ~PacketInf() { }
    virtual void ToString() const { }

    virtual void Read(char*& buffer) = 0;
    virtual void Write(char*& buffer) const = 0;
    virtual size_t Size() const = 0;
};

typedef vector<PacketInf*> PacketPtrVector;

class PacketHelper
{
public:
    static size_t ToBuffer(const PacketPtrVector& v, char*& buffer)
    {
	size_t size = TotalSize(v);
	buffer = new char[size];
	char* pBuffer = buffer;
	for (size_t i = 0; i < v.size(); ++i)
	{
	    v[i]->Write(pBuffer);
	}
	return size;
    }

    static size_t FromBuffer(const PacketPtrVector& v, char*& buffer)
    {
	size_t size = 0;
	for (size_t i = 0; i < v.size(); ++i)
	{
	    v[i]->Read(buffer);
	    size += v[i]->Size();
	}
	return size;
    }

    static size_t TotalSize(const PacketPtrVector& v)
    {
	size_t size = 0;
	for (size_t i = 0; i < v.size(); ++i)
	{
	    size += v[i]->Size();
	}
	return size;
    }
};

#include <cstring>

class BufferHelper
{
public:
    // this can be only used to read fixed size struct, 
    // and the struct size can be measured by sizeof().
    template<typename val_t>
    static void ReadVal(char*& buffer, val_t& val) 
    {
	val_t*& pVal = (val_t*&)buffer;
	val = *pVal++;
    }

    // this can be only used to write fixed size struct,
    // note the struct size will be measured by sizeof().
    template<typename val_t>
    static void WriteVal(char*& buffer, const val_t& val)
    {
	val_t*& pVal = (val_t*&)buffer;
	*pVal++ = val;
    }

    // put val, this won't move the pointer
    template<typename val_t>
    static void PutVal(char* buffer, const val_t& val)
    {
	*((val_t*)buffer) = val;
    }

    // get val, this won't move the pointer
    template<typename val_t>
    static void GetVal(const char* buffer, val_t& val)
    {
	val = *((val_t*)buffer);
    }

    // read std::string from buffer, 
    // the format should be {size_t|std::string}
    static void ReadString(char*& buffer, string& str)
    {
	size_t size = 0;
	ReadVal(buffer, size);
	str.assign(buffer, size);
	buffer += size;
    }

    // write std::string to buffer, 
    // the format will be {size_t|std::string}
    static void WriteString(char*& buffer, const string& str)
    {
	size_t size = str.size();
	WriteVal(buffer, size);
	memcpy(buffer, str.data(), size);
	buffer += size;
    }
};

#endif
