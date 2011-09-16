#ifndef TelBook_h
#define TelBook_h

#include <vector>
#include <string>
#include <map>
using namespace std;

typedef vector<string> StringArray;

class TelBook
{
    public:
	TelBook();
	~TelBook();

    public:
	bool load(const string&);
	bool save(const string&);

	bool insert(const string&, const StringArray&);
	bool remove(const string&);
	bool updateKey(const string&, const string&);
	bool updateValue(const string&, const StringArray&);

	StringArray searchByNumber(const string&);
	StringArray searchByName(const string&);

    private:
	map<string, StringArray> mNameMap;
	map<string, string> mNumberMap;
};

#endif
