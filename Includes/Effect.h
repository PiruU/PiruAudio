
// PiruAudio - Copyright (C) 2018 P. Bernardi
//
// See the LICENSE.txt file for license information.


#ifndef EFFECT_H
#define EFFECT_H

#include <map>
#include <string>
#include "portaudio.h"

class Effect {
    public :
        Effect(void(*)(float *, unsigned int, void *), void *);
        ~Effect();
        void apply(float *, unsigned int);
    private :
        void(*_transferFunction)(float *, unsigned int, void *);
        void *_parameters;
};

#endif
