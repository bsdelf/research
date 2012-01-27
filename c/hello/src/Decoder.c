#include "Decoder.h"

inline int decode_frame(struct Decoder* inf, int val) {
    return (inf->decode_frame)(inf->data, val);
}
