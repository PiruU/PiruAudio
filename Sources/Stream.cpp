
// PiruAudio - Copyright (C) 2018 P. Bernardi
//
// See the LICENSE.txt file for license information.


#include "Stream.h"


using namespace std;


Stream::Stream() : _paStream(0) {
    this->buildDefault();
}


Stream::~Stream() {
}


void Stream::buildDefaultInput(void) {
    Device defaultInputDevice     = getDefaultInputDevice();
    this->_input                  = setDefaultStreamParameters(&defaultInputDevice);
    this->_input.suggestedLatency = defaultInputDevice.defaultLowInputLatency();
}


void Stream::buildDefaultOutput(void) {
    Device defaultOutputDevice     = getDefaultOutputDevice();
    this->_output                  = setDefaultStreamParameters(&defaultOutputDevice);
    this->_output.suggestedLatency = defaultOutputDevice.defaultLowOutputLatency();
}


void Stream::buildDefault(void) {
    this->buildDefaultInput();
    this->buildDefaultOutput();
}


void Stream::open(vector<Effect> *effectsRack) {
    Pa_OpenStream(
        &(this->_paStream),
        &(this->_input),
        &(this->_output),
        getDefaultInputDevice().sampleRate(),
        FRAMES_PER_BUFFER,
        0,
        callback,
        effectsRack);
}


void Stream::start(void) {
    Pa_StartStream(this->_paStream);
}


void Stream::close(void) {
    Pa_CloseStream(this->_paStream);
}


void Stream::process(vector<Effect> *effectsRack) {
    this->open(effectsRack);
    this->start();
}


PaStreamParameters setDefaultStreamParameters(Device *device) {
    PaStreamParameters streamParameters;
    streamParameters.device                    = device->index();
    streamParameters.channelCount              = 1;
    streamParameters.sampleFormat              = PA_SAMPLE_TYPE;
    streamParameters.suggestedLatency          = device->defaultLowInputLatency();
    streamParameters.hostApiSpecificStreamInfo = 0;
    return streamParameters;
}


void initBuffers(const float *inputBuffer, float *outputBuffer, unsigned int nFrames) {
    for(unsigned int iFrame = 0; iFrame < nFrames; iFrame++) {
        outputBuffer[iFrame] = inputBuffer[iFrame];
    }
}


static int callback(
    const void *inputBuffer                 ,
    void *outputBuffer                      ,
    unsigned long framesPerBuffer           ,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags       ,
    void *userData
) {
    vector<Effect> *effectsRack = (vector<Effect> *)userData;
    initBuffers((const float *)inputBuffer, (float *)outputBuffer, framesPerBuffer);
    for(unsigned int iEffect = 0; iEffect < effectsRack->size(); iEffect++) {
        effectsRack->at(iEffect).apply((float *)outputBuffer, framesPerBuffer);
    }
    return paContinue;
}


