
// PiruAudio - Copyright (C) 2018 P. Bernardi
//
// See the LICENSE.txt file for license information.


#include "Delay.h"

void delayTransferFunction(float *output, unsigned int nFrames, void *parameters) {
    DelayData *delayData = (DelayData *)parameters;
    for(unsigned int iFrame = 0; iFrame < nFrames; iFrame++) {
        // emulate multiples echos
        output[iFrame] += delayData->amplitude * delayData->delayLine.read();
        delayData->delayLine.replace(output[iFrame]);
        delayData->delayLine.turn();
    }
}
