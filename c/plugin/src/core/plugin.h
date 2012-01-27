#ifndef PLUGIN_H
#define PLUGIN_H

#include <string>
#include <dlfcn.h>
#include "scx/Signal.hpp"

enum PluginType {
    PluginEmpty = 0,
    PluginCalculator,
    PluginForFoo
};

enum SigSenderType {
    SigSenderFoo = 0,
    SigSenderEvt
};

#define DEF_PLUGIN_COMMON_FNS(Plugin) \
extern "C" {		\
\
IPlugin* CreatePlugin() {   \
    return new Plugin;	    \
}			    \
\
void ReleasePlugin(IPlugin* plugin) {	\
    if (plugin != NULL)			\
	delete plugin;			\
}					\
\
} struct __end__


class IPlugin {
public:
    virtual ~IPlugin() { }

public:
    virtual int GetType() const = 0;
    virtual int GetVersion() const = 0;
    virtual std::string GetDesc() const = 0;
};

class BaseFoo {
public:
    scx::Signal<void (int)> sig1;
    scx::Signal<void (void)> sig2;
};

class BaseEvt {
public:
    scx::Signal<void (const char*)> sig1;
};

class ICalculator: public IPlugin {
public:
    virtual ~ICalculator() { }

public:
    virtual void PerformCal() = 0;
};

class IForFoo: public IPlugin {
public:
    virtual ~IForFoo() { }

public:
    virtual bool SetSigSender(void* sender, SigSenderType) = 0;
};

class PluginInf {
    typedef IPlugin* (*FnCreatePlugin)(void);
    typedef void (*FnReleasePlugin)(IPlugin*);

public:
    explicit PluginInf(const std::string& path) {
	handle = dlopen(path.c_str(), RTLD_LAZY | RTLD_GLOBAL);
	fnCreate = (FnCreatePlugin)dlsym(handle, "CreatePlugin");
	fnRelease = (FnReleasePlugin)dlsym(handle, "ReleasePlugin");
    }

    ~PluginInf() {
	dlclose(handle);
    }

    IPlugin* Create() {
	return fnCreate();
    }

    void Release(IPlugin* plugin) {
	fnRelease(plugin);
    }

private:
    void* handle;
    FnCreatePlugin fnCreate;
    FnReleasePlugin fnRelease;
};


#endif
