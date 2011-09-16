#ifndef Ogre_h
#define Ogre_h

#include "BaseRole.h"
#include <iostream>
using namespace std;

class Ogre: public BaseRole
{
    public:
	~Ogre()
	{
	    cout << "ogre destroyed" << endl;
	}

	virtual void Action()
	{
	    cout << "I am ogre!" << endl;
	}
};

#endif
