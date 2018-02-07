
// PiruAudio - Copyright (C) 2018 P. Bernardi
//
// See the LICENSE.txt file for license information.


#include <stdio.h>
#include <vector>
#include "Stream.h"
#include "Effect.h"
#include "AtanFuzz.h"

using namespace std;


int main(int argc, char *argv[]) {
    Pa_Initialize();

    vector<Effect> effectsRack;

    // set fuzz effect
    FuzzData fuzzData;
    fuzzData.slope = 70.0;
    Effect fuzz(atanFuzzTransferFunction, &fuzzData);
    effectsRack.push_back(fuzz);

    Stream defaultStream;
    defaultStream.process(&effectsRack);
    printf("Hit ENTER to stop program.\n");
    getchar();
    defaultStream.close();

    Pa_Terminate();
}


