#ifndef Sinbad_h
#define Sinbad_h

#include "BaseRole.h"
#include <iostream>
using namespace std;

class Sinbad: public Mixed
{
public:
    ~Sinbad()
    {
        cout << "sinbad destroyed" << endl;
    }

    virtual void Action()
    {
        cout << "I am sinbad!" << endl;
    }

    virtual int GetIndex() 
    {
        cout << "GlNode::GetIndex()" << endl;
        return 22;
    }
};

#endif
