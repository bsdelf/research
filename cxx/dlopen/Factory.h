#ifndef Factory_h
#define Factory_h

#include "BaseRole.h"
#include "Ogre.h"
#include "Sinbad.h"
#include "Agent.h"

extern "C"
{
    void* CreateRole(RoleType type)
    {
        void* role = NULL;
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

    void DestroyOgre(void* p)
    {
        BaseRole* role = static_cast<Ogre*>(p);
        delete role;
    }

    void DestroySinbad(void* p)
    {
        Sinbad* role = static_cast<Sinbad*>(p);
        delete role;
    }

    void* CreateAgent()
    {
        return new Agent;
    }

    void FreeAgent(void* _ptr)
    {
        Agent* ptr = (Agent*)_ptr;
        delete ptr;
    }
}

#endif
