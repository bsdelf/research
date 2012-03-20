#include "BaseRole.h"
#include "Ogre.h"
#include "Sinbad.h"
#include <iostream>
using namespace std;

class Agent: public IAgent
{
public:
    virtual BaseRole* CreateOgre()
    {
        return new Ogre;
    }

    virtual void FreeOgre(BaseRole* _ptr)
    {
        Ogre* ptr = (Ogre*)_ptr;
        delete ptr;
    }

    virtual BaseRole* CreateSinbad()
    {
        Sinbad* sinbad = new Sinbad();
        BaseRole* role = static_cast<BaseRole*>(sinbad);
        GlNode* glnode = static_cast<GlNode*>(sinbad);
        m_RoleGlNodeOffset = reinterpret_cast<long>(role) - reinterpret_cast<long>(glnode);
        cout << "works?" << glnode->GetIndex() << endl;
        cout << "offset:" << m_RoleGlNodeOffset << endl;
        return sinbad;
    }

    virtual void FreeSinbad(BaseRole* _ptr)
    {
        Sinbad* ptr = (Sinbad*)_ptr;
        delete ptr;
    }

    virtual GlNode* SinbadToGlNode(BaseRole* _ptr)
    {
        long nodePos = reinterpret_cast<long>(_ptr) - m_RoleGlNodeOffset;
        return reinterpret_cast<GlNode*>(nodePos);
    }

    virtual GlNode* DirectSinbadToGlNode(BaseRole* _ptr)
    {
        Sinbad* ptr = dynamic_cast<Sinbad*>(_ptr);
        return static_cast<GlNode*>(ptr);
    }

private:
    long m_RoleGlNodeOffset;
};
