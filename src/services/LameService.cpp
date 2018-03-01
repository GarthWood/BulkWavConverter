//
// Created by Garth on 2018/03/01.
//

#include "LameService.h"

LameService::LameService()
{

}

LameService::~LameService()
{

}

lame_t LameService::createLameInstance(int sampleRate, int numChannels)
{
    lame_t lame = lame_init();

    lame_set_in_samplerate(lame, sampleRate);
    lame_set_num_channels(lame, numChannels);
    lame_set_quality(lame, 5);
    lame_set_VBR(lame, vbr_default);

    lame_init_params(lame);

    return lame;
}

void LameService::destroyLameInstance(lame_t lame)
{
    lame_close(lame);
}