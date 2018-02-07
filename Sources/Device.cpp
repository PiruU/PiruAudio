
// PiruAudio - Copyright (C) 2018 P. Bernardi
//
// See the LICENSE.txt file for license information.


#include "Device.h"

Device::Device(unsigned int iDevice) : _info(0), _index(-1) {
    if(deviceIndexIsValid(iDevice)) {
        this->_info  = Pa_GetDeviceInfo(iDevice);
        this->_index = (int)iDevice; 
    }
}


Device::~Device() {
}


const char *Device::name(void) const {
    return this->_info->name;
}


bool Device::isValid(void) const {
    bool isDeviceValid = false;
    if(this->_info != 0) {
        isDeviceValid = true;
    }
    return isDeviceValid;
}


bool Device::isDefaultInput(void) const {
    bool isDeviceDefaultInput = false;
    if(this->_index == Pa_GetDefaultInputDevice()) {
        isDeviceDefaultInput = true;
    }
    return isDeviceDefaultInput;
}


bool Device::isDefaultOutput(void) const {
    bool isDeviceDefaultOutput = false;
    if(this->_index == Pa_GetDefaultOutputDevice()) {
        isDeviceDefaultOutput = true;
    }
    return isDeviceDefaultOutput;
}


bool deviceIndexIsValid(unsigned int iDevice) {
    bool isDeviceIndexValid = false;
    if(iDevice < Pa_GetDeviceCount()) {
        isDeviceIndexValid = true;
    }
    return isDeviceIndexValid;
}


unsigned int Device::index(void) const {
    return this->_index;
}


unsigned int Device::sampleRate(void) const {
    return this->_info->defaultSampleRate;
}


double Device::defaultLowInputLatency(void) const {
    return this->_info->defaultLowInputLatency;
}


double Device::defaultLowOutputLatency(void) const {
    return this->_info->defaultLowOutputLatency;
}


Device getDefaultInputDevice(void) {
    return Device(Pa_GetDefaultInputDevice());
}


Device getDefaultOutputDevice(void) {
    return Device(Pa_GetDefaultOutputDevice());
}

