//
// Created by Garth on 2018/03/01.
//

#ifndef BULKWAVCONVERTER_LAMESERVICE_H
#define BULKWAVCONVERTER_LAMESERVICE_H

#include <lame.h>

class LameService {

public:
    LameService();
    virtual ~LameService();

    lame_t createLameInstance(int sampleRate, int numChannels);

    void destroyLameInstance(lame_t lame);
};

typedef LameService* LameServicePtr;

#endif //BULKWAVCONVERTER_LAMESERVICE_H
