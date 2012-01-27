#include "../core/plugin.h"
#include "../core/plugininf.h"
#include <iostream>
using namespace std;

class ForFoo: public IForFoo {
public:
    ForFoo(): 
	mFoo(NULL), mEvt(NULL) {

    }

    ~ForFoo() {
	if (mFoo != NULL) {
	    mFoo->sig1.DisconnectReceiver(this);
	}
	if (mEvt != NULL) {
	    mEvt->sig1.DisconnectReceiver(this);
	}
    }

    virtual int GetType() const {
	return PluginForFoo;
    }

    virtual int GetVersion() const {
	return 1;
    }

    virtual std::string GetDesc() const {
	return "test receive signal";
    }

public:
    virtual bool SetSigSender(void* sender, SigSenderType type) {
	switch (type) {
	case SigSenderFoo: {
	    mFoo = (BaseFoo*)sender;
	    mFoo->sig1.Connect(&ForFoo::OnFooSig1, this);
	}
	    break;

	case SigSenderEvt: {
	    mEvt = (BaseEvt*)sender;
	    mEvt->sig1.Connect(&ForFoo::OnEvtSig1, this);
	}
	    break;

	default:
	    return false;
	}
	return true;
    }

private:
    void OnFooSig1(int val) {
	cout << "ForFoo, OnFooSig1:" << val << endl;
    }

    void OnEvtSig1(const char* val) {
	cout << "ForFoo, OnEvtSig1:" << val << endl;
    }

private:
    BaseFoo* mFoo;
    BaseEvt* mEvt;
};

DEF_PLUGIN_COMMON_FNS(ForFoo);
