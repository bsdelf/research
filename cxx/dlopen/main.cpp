#include <iostream>
using namespace std;

#include <dlfcn.h>
#include "BaseRole.h"

int main()
{
    typedef BaseRole* (*PtrCreateRole)(RoleType);
    typedef void (*PtrDestroyRole)(BaseRole*);

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

    PtrDestroyRole pDestroyRole = (PtrDestroyRole)dlsym(pFactory, "DestroyRole");
    if (pCreateRole == NULL)
    {
	cout << "bad pDestroyRole" << endl;
	return -1;
    }

    BaseRole* role;

    char ch;
    cin >> ch;
    
    role = pCreateRole(RoleSinbad); 
    role->Action();
    
    delete role;

    role = pCreateRole(RoleOgre);
    role->Action();
    pDestroyRole(role);

    dlclose(pFactory);

    cin >> ch;

    return 0;
}
