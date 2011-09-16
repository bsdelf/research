#ifndef Sinbad_h
#define Sinbad_h

#include "BaseRole.h"
#include <iostream>
using namespace std;

class Sinbad: public BaseRole
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
};

#endif
