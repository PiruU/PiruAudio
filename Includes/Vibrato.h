
// PiruAudio - Copyright (C) 2018 P. Bernardi
//
// See the LICENSE.txt file for license information.


#ifndef VIBRATO_H
#define VIBRATO_H

#include <cmath>
#include "Constants.h"

typedef struct VibratoData {
    float phase;
    float amplitude;
    float frequency;
    float frameRate;
} VibratoData;

void applyVibrato(float *, unsigned int, void *);
void updateVibratoPhase(void *);
void vibratoTransferFunction(float *, unsigned int, void *);

#endif
