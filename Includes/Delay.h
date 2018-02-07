
// PiruAudio - Copyright (C) 2018 P. Bernardi
//
// See the LICENSE.txt file for license information.


#ifndef DELAY_H
#define DELAY_H

#include "Chain.h"

typedef struct DelayData {
    float amplitude;
    Chain<float> delayLine;
} DelayData;

void delayTransferFunction(float *, unsigned int, void *);

#endif
