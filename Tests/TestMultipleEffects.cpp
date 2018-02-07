
// PiruAudio - Copyright (C) 2018 P. Bernardi
//
// See the LICENSE.txt file for license information.


#include <stdio.h>
#include <vector>
#include "Stream.h"
#include "Effect.h"
#include "Vibrato.h"
#include "AtanFuzz.h"
#include "Delay.h"

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


    // set delay effect
    DelayData delayData;
    delayData.amplitude = 0.7;
    delayData.delayLine = Chain<float> (22050, 0.0);
    Effect delay(delayTransferFunction, &delayData);
    effectsRack.push_back(delay);

    // set fuzz effect
    FuzzData fuzzData;
    fuzzData.slope = 50.0;
    Effect fuzz(atanFuzzTransferFunction, &fuzzData);
    effectsRack.push_back(fuzz);

    Stream defaultStream;
    defaultStream.process(&effectsRack);
    printf("Hit ENTER to stop program.\n");
    getchar();
    defaultStream.close();


    Pa_Terminate();
}


