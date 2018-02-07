
// PiruAudio - Copyright (C) 2018 P. Bernardi
//
// See the LICENSE.txt file for license information.


#ifndef DEVICE_H
#define DEVICE_H

#include "portaudio.h"

class Device {
    public :
        Device(unsigned int iDevice);
        ~Device();
        bool isValid(void) const;
        bool isDefaultInput(void) const;
        bool isDefaultOutput(void) const;
        const char *name(void) const;
        unsigned int index(void) const;
        unsigned int sampleRate(void) const;
        double defaultLowInputLatency(void) const;
        double defaultLowOutputLatency(void) const;
    private :
        const PaDeviceInfo *_info;
        int _index;
};

bool deviceIndexIsValid(unsigned int);
Device getDefaultInputDevice(void);
Device getDefaultOutputDevice(void);



#endif
