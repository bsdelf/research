#ifndef BaseRole_h
#define BaseRole_h

#include <iostream>
using namespace std;

enum RoleType
{
    RoleOgre,
    RoleSinbad
};


class BaseRole
{
public: 
    virtual ~BaseRole()
    {
        cout << "BaseRole::~()" << endl;
    }

    virtual void Action() = 0;
};

class GlNode
{
public:
    virtual ~GlNode()
    {
        cout << "GlNode::~()" << endl;
    }

    virtual int GetIndex() = 0;
};

class Mixed: public BaseRole, public GlNode
{
public:
    virtual ~Mixed()
    {
        cout << "Mixed::~()" << endl;
    }
};

class IAgent
{
public:
    virtual ~IAgent() { }

    virtual BaseRole* CreateOgre() = 0;
    virtual void FreeOgre(BaseRole*) = 0;
    virtual BaseRole* CreateSinbad() = 0;
    virtual void FreeSinbad(BaseRole*) = 0;

    virtual GlNode* SinbadToGlNode(BaseRole* _ptr) = 0;
    virtual GlNode* DirectSinbadToGlNode(BaseRole* _ptr) = 0;
};

#endif
