
// PiruAudio - Copyright (C) 2018 P. Bernardi
//
// See the LICENSE.txt file for license information.


#ifndef FLANGER_H
#define FLANGER_H

#include <cmath>
#include "Constants.h"
#include "Chain.h"

typedef struct FlangerData {
    unsigned int delayMin;
    unsigned int delayMax;
    unsigned int delay;
    int delayIncrease;
    float frequency;
    float amplitude;
    float frameRate;
    float phase;
    Chain<float> delayLine;
} FlangerData;

void updateFlangerPhase(FlangerData *);
void updateFlangerDelay(FlangerData *);
void updateFlangerDelayLine(FlangerData *);
void updateFlanger(FlangerData *);
unsigned int getDelay(FlangerData *);
void flangerTransferFunction(float *, unsigned int, void *);

#endif
