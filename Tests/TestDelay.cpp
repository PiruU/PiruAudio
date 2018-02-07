
// PiruAudio - Copyright (C) 2018 P. Bernardi
//
// See the LICENSE.txt file for license information.


#include <stdio.h>
#include <vector>
#include "Stream.h"
#include "Effect.h"
#include "Delay.h"

using namespace std;


int main(int argc, char *argv[]) {
    Pa_Initialize();

    vector<Effect> effectsRack;

    // set delay effect
    DelayData delayData;
    delayData.amplitude = 0.5;
    delayData.delayLine = Chain<float> (10000, 0.0);
    Effect delay(delayTransferFunction, &delayData);
    effectsRack.push_back(delay);

    Stream defaultStream;
    defaultStream.process(&effectsRack);
    printf("Hit ENTER to stop program.\n");
    getchar();
    defaultStream.close();

    Pa_Terminate();
}


