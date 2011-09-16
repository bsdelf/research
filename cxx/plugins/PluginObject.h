#ifndef PluginObject_h
#define PluginObject_h

namespace mous::plugin {

enum PluginType
{
    Decoder,
    Encoder
};

class PluginObject
{
public:
    PluginObject()
    {
	setType();
    }

    virtual ~PluginObject()
    {
    }

    virtual void setType() = 0;
};

}

#endif
