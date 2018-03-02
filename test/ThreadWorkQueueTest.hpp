/**
 * Author: Garth Wood
 * Date: 02 March 2018
 *
 * Unit test for the ThreadWorkQueue
 */

#ifndef BULKWAVCONVERTER_THREADWORKQUEUETEST_H
#define BULKWAVCONVERTER_THREADWORKQUEUETEST_H

#include <gtest/gtest.h>
#include "../src/threading/ThreadWorkQueue.h"
#include "ThreadTaskTest.hpp"

#define TEST_TASK_1_NAME      "TestTask1"
#define TEST_TASK_2_NAME      "TestTask2"

class ThreadWorkQueueTest : public ::testing::Test
{
protected:
    /**
     * Sets up the test
     */
    virtual void SetUp()
    {
        mQueue.addTask(new ThreadTaskTest(TEST_TASK_1_NAME));
        mQueue.addTask(new ThreadTaskTest(TEST_TASK_2_NAME));
    }

    ThreadWorkQueue mQueue;
};

/**
 *  Validates that the correct task is returned from the queue
 */
TEST_F(ThreadWorkQueueTest, NextTaskRetrievesFirstTask)
{
    ThreadTaskTest* task = static_cast<ThreadTaskTest*>(mQueue.nextTask());

    ASSERT_STREQ(task->getName(), TEST_TASK_1_NAME);
}

#endif // BULKWAVCONVERTER_THREADWORKQUEUETEST_H
