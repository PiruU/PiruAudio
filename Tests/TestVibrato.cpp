
// PiruAudio - Copyright (C) 2018 P. Bernardi
//
// See the LICENSE.txt file for license information.


#include <stdio.h>
#include <vector>
#include "Stream.h"
#include "Effect.h"
#include "Vibrato.h"

using namespace std;


int main(int argc, char *argv[]) {
    Pa_Initialize();

    vector<Effect> effectsRack;

    // set vibrato effect
    VibratoData vibratoData;
    vibratoData.phase     = 0.0;
    vibratoData.amplitude = 0.30;
    vibratoData.frequency = 4.0;
    vibratoData.frameRate = getDefaultInputDevice().sampleRate();
    Effect vibrato(vibratoTransferFunction, &vibratoData);
    effectsRack.push_back(vibrato);

    Stream defaultStream;
    defaultStream.process(&effectsRack);
    printf("Hit ENTER to stop program.\n");
    getchar();
    defaultStream.close();

    Pa_Terminate();
}


