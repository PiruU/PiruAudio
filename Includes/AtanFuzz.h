
// PiruAudio - Copyright (C) 2018 P. Bernardi
//
// See the LICENSE.txt file for license information.


#ifndef ATANFUZZ_H
#define ATANFUZZ_H

#include <cmath>

typedef struct FuzzData {
    float slope;
} FuzzData;

void atanFuzzTransferFunction(float *, unsigned int, void *);

#endif
