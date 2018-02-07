
// PiruAudio - Copyright (C) 2018 P. Bernardi
//
// See the LICENSE.txt file for license information.


#include "AtanFuzz.h"

using namespace std;

// Non-linear amplifier with atan distortion curve
void atanFuzzTransferFunction(float *output, unsigned int nFrames, void *parameters)
{
    FuzzData *fuzzData = (FuzzData *)parameters;
    for(unsigned int iFrame = 0; iFrame < nFrames; iFrame++) {
        output[iFrame] = 2.0 / 3.15 * atan(output[iFrame] * fuzzData->slope);
    }
}

