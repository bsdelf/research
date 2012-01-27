#include <iostream>
#include <string>
#include <vector>

#include <ftw.h>

#include "plugin.h"
using namespace std;

vector<string>* dirs = NULL;
int OnDir(const char* file, const struct stat* s, int) {
    if (!(s->st_mode & S_IFDIR))
	dirs->push_back(file);
    return 0;
}

void ShowPlugins(const vector<IPlugin*>& plugins) {
    for (size_t i = 0; i < plugins.size(); ++i) {
	IPlugin* plugin = plugins[i];
	cout << i << ". Desc:" << plugin->GetDesc();
	cout << "\t Version:" << plugin->GetVersion() << endl;
    }
}

class Foo: public BaseFoo {
public:
    void test() {
	sig1(1987);
    }
};

class Evt: public BaseEvt {
public:
    void test() {
	sig1("hello world!");
    }
};

int main() {
    vector<string> pluginList;
    vector<PluginInf*> pluginInfs;
    vector<IPlugin*> plugins;

    Foo foo;
    Evt evt;

    dirs = &pluginList;
    ftw("./plugins", &OnDir, 1);

    pluginInfs.resize(pluginList.size());
    plugins.resize(pluginList.size());
    cout << "# Loading.." << endl;
    for (size_t i = 0; i < pluginList.size(); ++i) {
	cout << pluginList[i] << endl;

	pluginInfs[i] = new PluginInf(pluginList[i]);
	plugins[i] = pluginInfs[i]->Create();

	IPlugin* p = plugins[i];
	if (p->GetType() == PluginForFoo) {
	    IForFoo* forfoo = (IForFoo*)p;
	    forfoo->SetSigSender(&foo, SigSenderFoo);
	    forfoo->SetSigSender(&evt, SigSenderEvt);
	}
    }
    cout << "# Done!" << endl;

    while (true) {
	ShowPlugins(plugins);
	int op = 0;
	cin >> op;
	if (op < 0)
	    break;
	else if (op >= (int)plugins.size()) {
	    cout << "No such plugin!" << endl;
	} else {
	    IPlugin* p = plugins[op];
	    switch (p->GetType()) {
	    case PluginCalculator: {
		ICalculator* c = (ICalculator*)p;
		c->PerformCal();
	    }
		break;

	    case PluginForFoo: {
		foo.test();
		evt.test();
	    }
		break;
	    }
	}
    }

    cout << "# Cleanup.." << endl;
    for (size_t i = 0; i < plugins.size(); ++i) {
	pluginInfs[i]->Release(plugins[i]);
	delete pluginInfs[i];
    }
    cout << "# Done!" << endl;

    return 0;
}
