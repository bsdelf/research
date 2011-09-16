#ifndef Factory_h
#define Factory_h

#include "BaseRole.h"
#include "Ogre.h"
#include "Sinbad.h"

extern "C"
{
    BaseRole* CreateRole(RoleType type)
    {
	BaseRole* role = NULL;
	switch (type)
	{
	    case RoleOgre:
		role = new Ogre();
		break;

	    case RoleSinbad:
		role = new Sinbad();
		break;
	}

	return role;
    }

    void DestroyRole(BaseRole* role)
    {
	delete role;
	role = NULL;
    }

}

#endif
