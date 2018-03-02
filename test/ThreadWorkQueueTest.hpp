//
// Created by Garth on 2018/03/02.
//

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
    ThreadWorkQueueTest()
    {
    }

    virtual ~ThreadWorkQueueTest()
    {
    }

    virtual void SetUp()
    {
        queue.addTask(new ThreadTaskTest(TEST_TASK_1_NAME));
        queue.addTask(new ThreadTaskTest(TEST_TASK_2_NAME));
    }

    virtual void TearDown()
    {
    }

    ThreadWorkQueue queue;
};


TEST_F(ThreadWorkQueueTest, NextTaskRetrievesFirstTask)
{
    ThreadTaskTest* task = static_cast<ThreadTaskTest*>(queue.nextTask());

    ASSERT_STREQ(task->getName(), TEST_TASK_1_NAME);
}

#endif //BULKWAVCONVERTER_THREADWORKQUEUETEST_H
