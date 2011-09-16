#include <iostream>
using namespace std;

class Mp3Decoder
{
    public:
	void Read()
	{
	    cout << "read mp3" << endl;
	}
};

class OggDecoder
{
    public:
	void Read()
	{
	    cout << "read ogg" << endl;
	}
};

class ApeDecoder
{
    public:
	void Read()
	{
	    cout << "read ape" << endl;
	}
};

template <typename D>
class DecoderWrapper
{
    public:
	void StartBufferring()
	{
	}

	void StopBufferring()
	{
	}

	void Read()
	{
	    cout << "Decoder Wrapper ";
	    mDecoder.Read();
	}

    private:
	D mDecoder;
};

template <typename D>
void ReadOnce(D& decoder)
{
    decoder.Read();
}

int main(int argc, char** argv)
{
    DecoderWrapper<Mp3Decoder> mp3;
    DecoderWrapper<OggDecoder> ogg;
    DecoderWrapper<ApeDecoder> ape;

    while (true)
    {
	char ch;
	cin >> ch;

	switch (ch)
	{
	    case 'm':
		ReadOnce(mp3);
		break;

	    case 'o':
		ReadOnce(ogg);
		break;

	    case 'a':
		ReadOnce(ape);
		break;

	    case 'q':
		return 0;

	    default:
		break;
	}
    }

    return 0;
}
