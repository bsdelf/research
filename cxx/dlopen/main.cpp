#include <iostream>
using namespace std;

#include <dlfcn.h>
#include "BaseRole.h"

int main()
{
    typedef void* (*PtrCreateRole)(RoleType);
    typedef void (*PtrDestroyOgre)(void*);
    typedef void (*PtrDestroySinbad)(void*);

    typedef void* (*FnCreate)(void);
    typedef void (*FnFree)(void*);

    string path = "./Factory.so";
    void* pFactory = dlopen(path.c_str(), RTLD_LAZY);
    if (pFactory == NULL)
    {
        cout << "bad factory" << endl;
        cout << dlerror() << endl;
        return -1;
    }

    PtrCreateRole pCreateRole = (PtrCreateRole)dlsym(pFactory, "CreateRole");
    if (pCreateRole == NULL)
    {
        cout << "bad pCreateRole" << endl;
        return -1;
    }

    PtrDestroyOgre pDestroyOgre = (PtrDestroyOgre)dlsym(pFactory, "DestroyOgre");
    PtrDestroySinbad pDestroySinbad = (PtrDestroySinbad)dlsym(pFactory, "DestroySinbad");
    if (pCreateRole == NULL)
    {
        cout << "bad pDestroyRole" << endl;
        return -1;
    }

    BaseRole* role;
    GlNode* node;

    Mixed* sbd = (Mixed*)pCreateRole(RoleSinbad); 

    role = (BaseRole*)sbd; 
    role->Action();
    node = (GlNode*)sbd;
    cout << node->GetIndex() << endl;
    pDestroySinbad(sbd);

    cout << endl;

    role = (BaseRole*)pCreateRole(RoleOgre);
    role->Action();
    pDestroyOgre(role);

    cout << endl;
    cout << ">>>> test agent" << endl;
    {
        FnCreate fnCreateAgent = (FnCreate)dlsym(pFactory, "CreateAgent");
        FnFree fnFreeAgent = (FnFree)dlsym(pFactory, "FreeAgent");
        IAgent* agent = (IAgent*)fnCreateAgent();

        BaseRole* role = NULL;
        role = (BaseRole*)agent->CreateOgre();
        role->Action();
        agent->FreeOgre(role);

        role = (BaseRole*)agent->CreateSinbad();
        role->Action();

        GlNode* node = agent->SinbadToGlNode(role);
        cout << node->GetIndex() << endl;

        node = agent->DirectSinbadToGlNode(role);
        cout << node->GetIndex() << endl;

        agent->FreeSinbad(role);

        fnFreeAgent(agent);
    }

    dlclose(pFactory);
    return 0;
}
