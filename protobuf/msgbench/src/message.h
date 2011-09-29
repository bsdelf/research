#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include "errno.h"
using namespace std;

class Message
{
public:
    Message(const size_t type):
        m_Type(type),
        m_FieldNum(0),
        m_BodySize(0),
        m_Head(NULL),
        m_Body(NULL),
        m_Data(NULL),
        m_HeadSize(sizeof(size_t)*3),
        m_TotalSize(sizeof(size_t)*3)
    {
        m_Head = new char[m_HeadSize];
    }

    ~Message()
    {
        if (m_Head != NULL)
            delete[] m_Head;
        if (m_Body != NULL)
            delete[] m_Body;
        if (m_Data != NULL)
            delete[] m_Data;
    }
    
    void appendField(const string& field)
    {
        m_FieldNum += 1;
        m_BodySize += field.size() + 1;
        m_TotalSize = m_HeadSize + m_BodySize;
        m_FieldVector.push_back(field);
    }

    string& getField(size_t index)
    {
        return m_FieldVector[index];
    }

    char* head()
    {
        return m_Head;
    }

    char* body()
    {
        return m_Body;
    }

    char* data()
    {
        return m_Data;
    }

    size_t headSize()
    {
        return m_HeadSize;
    }

    size_t fieldNum()
    {
        return m_FieldNum;
    }

    size_t bodySize()
    {
        return m_BodySize;
    }

    size_t totalSize()
    {
        return m_TotalSize;
    }

    int decodeHead()
    {
        size_t offset = 0;
        char data[sizeof(size_t)] = "";

        memcpy(data, &m_Head[offset], sizeof(size_t));
        if (atoi(data) != m_Type)
            return ERR_TYPE;
        offset += sizeof(size_t);

        memcpy(data, &m_Head[offset], sizeof(size_t));
        m_FieldNum = atoi(data);
        if (m_FieldNum == 0)
            return ERR_FIELDNUM;
        offset += sizeof(size_t);

        memcpy(data, &m_Head[offset], sizeof(size_t));
        m_BodySize = atoi(data);
        if (m_BodySize == 0)
            return ERR_BODYSIZE;

        m_Body = new char[m_BodySize];

        return 0;
    }

    int decodeBody()
    {
        size_t length = 0;
        size_t offset = 0;
        for (size_t i = 0; i < m_FieldNum; ++i)
        {
            length = strlen(&m_Body[offset]);
            string field(&m_Body[offset], length);
            m_FieldVector.push_back(field);
            offset += length + 1;
        }
        return 0;
    }

    int encode()
    {
        delete[] m_Head;
        m_Head = NULL;

        m_Data = new char[m_TotalSize];
        memset(m_Data, 0, m_TotalSize);

        size_t offset = 0;
        char data[sizeof(size_t)+1] = "";
        
        sprintf(data, "%4d", m_Type);
        memcpy(&m_Data[offset], data, sizeof(size_t));
        offset += sizeof(size_t);

        sprintf(data, "%4d", m_FieldNum);
        memcpy(&m_Data[offset], data, sizeof(size_t));
        offset += sizeof(size_t);

        sprintf(data, "%4d", m_BodySize);
        memcpy(&m_Data[offset], data, sizeof(size_t));
        offset += sizeof(size_t);

        for (size_t i = 0; i < m_FieldNum; ++i)
        {
            memcpy(&m_Data[offset], m_FieldVector[i].data(), m_FieldVector[i].size());
            offset += m_FieldVector[i].size() + 1;
        }

        return 0;
    }
    
private:
    const size_t m_Type;
    size_t m_FieldNum;
    size_t m_BodySize;
    char* m_Head;
    char* m_Body;
    char* m_Data;
    const size_t m_HeadSize;
    size_t m_TotalSize;
    vector<string> m_FieldVector;
};

string static covIntStr(int data)
{
    stringstream stream;
    stream << data;
    return stream.str();
}

int static covStrInt(string& data)
{
    int value = 0;
    stringstream stream;
    stream << data;
    stream >> value;
    return value;
}

#endif
