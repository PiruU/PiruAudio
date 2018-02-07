
// PiruAudio - Copyright (C) 2018 P. Bernardi
//
// See the LICENSE.txt file for license information.


#include "Flanger.h"

void updateFlangerPhase(FlangerData *flanger) {
    float timeStep  = 1.0 / flanger->frameRate;
    float pulsation = 2 * PI * flanger->frequency;
    float phase     = flanger->phase;
    phase += timeStep* pulsation;
    if(phase > 2 * PI) {
        phase -= 2 * PI;
    }
    flanger->phase = phase;
}


unsigned int getDelay(FlangerData *flanger) {
    float cs   = cos(flanger->phase);
    float iMin = (float)flanger->delayMin;
    float iMax = (float)flanger->delayMax;
    return (unsigned int)(0.5 * (iMax * (1 + cs) + iMin * (1 - cs)));
}


void updateFlangerDelay(FlangerData *flanger) {
    float previousDelay  = flanger->delay;
    flanger->delay = getDelay(flanger);
    flanger->delayIncrease = (int)flanger->delay - (int)previousDelay;
}

#include <iostream>

void updateFlangerDelayLine(FlangerData *flanger) {
    flanger->delayLine.moveReadBuffer(flanger->delayIncrease);
}


void updateFlanger(FlangerData *flanger) {
    updateFlangerDelay(flanger);
    updateFlangerDelayLine(flanger);
}


void flangerTransferFunction(float *output, unsigned int nFrames, void *parameters) {
    FlangerData *flanger = (FlangerData *)parameters;
    for(unsigned int iFrame = 0; iFrame < nFrames; iFrame++) {
        updateFlanger(flanger);
        flanger->delayLine.turn();
        output[iFrame] = 0.5 * (output[iFrame] + flanger->amplitude * flanger->delayLine.read());
        flanger->delayLine.replace(output[iFrame]);
	updateFlangerPhase(flanger);
    }
}





