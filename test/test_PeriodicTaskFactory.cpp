#include <gtest/gtest.h>
#include "PeriodicTaskFactory.h"

TEST(PeriodicTaskFactoryTest, CreatePeriodicTask) {
    // Check that createPeriodicTask returns a valid PeriodicTask object
    bool func_called = false;
    std::function<void(std::shared_ptr<Packet>&)> func =
        [&](std::shared_ptr<Packet>& packet) { func_called = true; };
    auto task = PeriodicTaskFactory::createPeriodicTask(1000, func);
    EXPECT_NE(task, nullptr);
}