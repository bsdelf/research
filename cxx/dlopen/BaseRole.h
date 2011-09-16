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
    BaseRole()
    {
    }

    virtual ~BaseRole()
    {
	cout << "destroyed" << endl;
    }

    virtual void Action() = 0;
};

#endif
