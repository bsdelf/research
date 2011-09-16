#include <ext/atomicity.h>
#include <iostream>
#include <vector>
using namespace std;

class test
{
    public:
	test()
	{
	    library_class_b* object_b = new library_class_b;
	    shared_object_a.add_b(&mData);
	}
	void append(int data)
	{
	    mData.push_back(data);
	}

	void remove(size_t index)
	{
	    mData.erase(mData.begin() + index);
	}

    private:
	vector<int> mData;
};

int main()
{
    return 0;
}
