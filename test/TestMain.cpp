/**
 * Author: Garth Wood
 * Date: 02 March 2018
 *
 * Entry point into the unit tests
 */

#include "ThreadWorkQueueTest.hpp"
#include <gtest/gtest.h>

/**
 * Unit testing entry point
 * @param argc The number of command line arguments
 * @param args The command line arguments
 * @return The result code
 */
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
