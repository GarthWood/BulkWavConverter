/**
 * Author: Garth Wood
 * Date: 02 March 2018
 *
 * A service to handle LAME instances
 */

#ifndef BULKWAVCONVERTER_LAMESERVICE_H
#define BULKWAVCONVERTER_LAMESERVICE_H

#include <lame.h>

class LameService
{
public:
    /**
     * Constructor
     */
    LameService();

    /**
     * Destructor
     */
    virtual ~LameService();

    /**
     * Creates a new LAME instance with the parameters provided
     * @param sampleRate The sample rate
     * @param numChannels The number of channels
     * @return A LAME instance
     */
    lame_t createLameInstance(int sampleRate, int numChannels);

    /**
     * Destroys the specified LAME instance
     * @param lame The lame instance
     */
    void destroyLameInstance(lame_t lame);
};

typedef LameService* LameServicePtr;

#endif // BULKWAVCONVERTER_LAMESERVICE_H
