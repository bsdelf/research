#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "point.h"

#include "String.h"

#include "Object.h"
#include "Decoder.h"
#include "Mp3Decoder.h"
#include "AacDecoder.h"

#include "IDecoder.hpp"
#include "CMp3Decoder.hpp"
#include "CAacDecoder.hpp"

#include "InfMp3Decoder.h"
#include "InfAacDecoder.h"
#include "InfDecoder.h"

#include "vdecoder.h"
#include "vmp3decoder.h"
#include "vaacdecoder.h"

#include "scx/RunTimer.hpp"

using namespace std;
using namespace scx;

int main()
{
    struct Mp3Decoder* mp3d = (struct Mp3Decoder*)create(Mp3Decoder);
    struct AacDecoder* aacd = (struct AacDecoder*)create(AacDecoder);
    struct Decoder* dec = NULL;

    dec = &mp3d->inf;
    printf("mp3d %d\n", decode_frame(dec, 4));
    dec = &aacd->inf;
    printf("aacd %d\n", decode_frame(dec, 4));

    CMp3Decoder* cmp3d = new CMp3Decoder;
    CAacDecoder* caacd = new CAacDecoder;
    IDecoder* id = NULL;

    id = cmp3d;
    cout << "cmp3d " << id->DecodeFrame(4) << endl;
    id = caacd;
    cout << "caacd " << id->DecodeFrame(4) << endl;

    InfMp3Decoder smp3 = {
	Mp3Vtable, 0
    };

    InfAacDecoder saac;
    aac_ini(&saac);

    InfDecoder* inf = NULL;

    inf = (struct InfDecoder*)&smp3;
    printf("smp3 %d\n", inf_decode_frame(inf, 4));
    inf = (struct InfDecoder*)&saac;
    printf("saac %d\n", inf_decode_frame(inf, 4));

    struct VDecoder* vd = NULL;
    struct VDecoder* vdmp3 = (struct VDecoder*) VMp3Decoder_ctor(NULL);
    struct VDecoder* vdaac = (struct VDecoder*) VAacDecoder_ctor(NULL);

    printf("vmp3 %d\n", VDecodeFrame(vdmp3, 4));
    printf("vaac %d\n", VDecodeFrame(vdaac, 4));
    printf("vmp3 desc %s\n", ((struct VMp3Decoder*)vdmp3)->desc);
    printf("vaac test %d\n", ((struct VAacDecoder*)vdaac)->test);

    {
	const int times = 99;
	const int loops = 9999999;
	double a = 0, b = 0, c = 0, d = 0;

	SCX_BENCH0("ooc\t", times, loops, 
		dec = j&1 ? &mp3d->inf : &aacd->inf; 
		a += decode_frame(dec, 4));
	cout << "\t" << a << "\t" << aacd->times << endl;
	sleep(1);

	SCX_BENCH0("inf c\t", times, loops,
		inf = j&1 ? (struct InfDecoder*)&smp3 : (struct InfDecoder*)&saac;
		c += inf_decode_frame(inf, 4));
	cout << "\t" << c << "\t" << inf_get_times(inf) << endl;
	sleep(1);

	SCX_BENCH0("vtbl c\t", times, loops,
		vd = j&1 ? vdmp3 : vdaac;
		d += VDecodeFrame(vd, 4));
	cout << "\t" << d << "\t" << vd->times << endl;

	SCX_BENCH0("c++\t", times, loops,
		id = j&1 ? (IDecoder*)cmp3d : (IDecoder*)caacd;
		b += id->DecodeFrame(4));
	cout << "\t" << b << "\t" << id->GetTimes() << endl;
    }

    struct String* stra = (struct String*)create(String, "hello world!");
    printf("String stra text: %s\n", stra->text);
    printf("string sizeof(stra): %d\n", sizeOf(stra));

    struct String* strb = (struct String*)clone(stra);
    printf("String text:%s\n", stra->text);

    release(stra);
    release(strb);

    return 0;
}
