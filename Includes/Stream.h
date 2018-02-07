
// PiruAudio - Copyright (C) 2018 P. Bernardi
//
// See the LICENSE.txt file for license information.


#ifndef STREAM_H
#define STREAM_H

#include <vector>

#include "portaudio.h"
#include "Device.h"
#include "Constants.h"
#include "Effect.h"

class Stream {
    public :
       Stream();
       ~Stream();
       void buildDefaultInput(void);
       void buildDefaultOutput(void);
       void buildDefault(void);
       void open(std::vector<Effect> *);
       void start(void);
       void close(void);
       void process(std::vector<Effect> *);
    private : 
        PaStreamParameters _input;
        PaStreamParameters _output;
        PaStream *_paStream;
};

PaStreamParameters setDefaultStreamParameters(Device *);
void initBuffers(const float *, float *, unsigned int);
static int callback(const void *, void *, unsigned long, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags, void *);

#endif
