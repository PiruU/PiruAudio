
// PiruAudio - Copyright (C) 2018 P. Bernardi
//
// See the LICENSE.txt file for license information.


#include "Effect.h"

using namespace std;

Effect::Effect(
    void (*transferFunction)(float *, unsigned int, void *),
    void *parameters) :
    _transferFunction(transferFunction), _parameters(parameters) {
}


Effect::~Effect() {
}


void Effect::apply(float *outputFrames, unsigned int nFrames) {
    this->_transferFunction(outputFrames, nFrames, this->_parameters);
}
