
// PiruAudio - Copyright (C) 2018 P. Bernardi
//
// See the LICENSE.txt file for license information.

#include "Vibrato.h"

using namespace std;

void applyVibrato(float *output, unsigned int nFrames, VibratoData *vibrato) {
    float time      = 0;
    float phase     = vibrato->phase;
    float amplitude = vibrato->amplitude;
    float pulsation = 2 * PI * vibrato->frequency;
    float timeStep  = 1.0 / vibrato->frameRate;
    for(unsigned int iFrame = 0; iFrame < nFrames; iFrame++) {
        phase += timeStep * pulsation;
        output[iFrame] *= 1 + amplitude * (cos(phase) - 1);
    }
    vibrato->phase = phase;
}


void updateVibratoPhase(VibratoData *vibrato) {
    float timeStep  = 1.0 / vibrato->frameRate;
    float pulsation = 2 * PI * vibrato->frequency;
    float phase     = vibrato->phase;
    phase += timeStep* pulsation;
    if(phase > 2 * PI) {
        phase -= 2 * PI;
    }
    vibrato->phase = phase;
}


void vibratoTransferFunction(float *output, unsigned int nFrames, void *parameters) {
    VibratoData *vibratoData = (VibratoData *)parameters;
    applyVibrato(output, nFrames, vibratoData);
    updateVibratoPhase(vibratoData);
}
