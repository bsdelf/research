#include "../core/plugin.h"
#include "../core/plugininf.h"
#include <iostream>
using namespace std;

class MulCalculator: public ICalculator {
public:
    virtual int GetType() const {
	return PluginCalculator;
    }

    virtual int GetVersion() const {
	return 1;
    }

    virtual std::string GetDesc() const {
	return "calculate a*b";
    }

public:
    virtual void PerformCal() {
	cout << "Input a, b for mul" << endl;
	int a, b;
	cin >> a >> b;
	cout << a << "*" << b << "=" << a*b << endl;
    }
};

DEF_PLUGIN_COMMON_FNS(MulCalculator);
