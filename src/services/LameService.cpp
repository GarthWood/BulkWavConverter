/**
 * Author: Garth Wood
 * Date: 02 March 2018
 *
 * A service to handle LAME instances
 */

#include "LameService.h"

#define ENCODING_QUALITY_BEST   2
#define ENCODING_QUALITY_GOOD   5
#define ENCODING_QUALITY_OK     7

/**
 * Constructor
 */
LameService::LameService()
{
}

/**
 * Destructor
 */
LameService::~LameService()
{
}

/**
 * Creates a new LAME instance with the parameters provided
 * @param sampleRate The sample rate
 * @param numChannels The number of channels
 * @return A LAME instance
 */
lame_t LameService::createLameInstance(int sampleRate, int numChannels)
{
    lame_t lame = lame_init();

    lame_set_in_samplerate(lame, sampleRate);
    lame_set_num_channels(lame, numChannels);
    lame_set_quality(lame, ENCODING_QUALITY_GOOD);
    lame_set_VBR(lame, vbr_default);

    lame_init_params(lame);

    return lame;
}

/**
 * Destroys the specified LAME instance
 * @param lame The lame instance
 */
void LameService::destroyLameInstance(lame_t lame)
{
    lame_close(lame);
}
