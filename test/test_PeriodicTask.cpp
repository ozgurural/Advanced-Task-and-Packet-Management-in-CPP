#include <gtest/gtest.h>
#include <functional>
#include "Packet.h"
#include "PeriodicTask.h"

class PeriodicTaskTest_SetFunction_Test : public ::testing::Test {
protected:
    PeriodicTask task;

    void SetUp() override {
        // Set a flag variable to false
        flag = false;
    }

    bool flag{};
};

TEST(PeriodicTaskTest, Constructor) {
    // Check that a new PeriodicTask object has a valid ID and an interval of 0
    std::function<void(std::shared_ptr<Packet>&)> func =
        [](std::shared_ptr<Packet>& packet) {};
    PeriodicTask task(0, func);
    EXPECT_NE(task.getId(), 0);
    EXPECT_EQ(task.getInterval(), 0);
    EXPECT_TRUE(PeriodicTask::scompareFunctions(task.getFunction(), func));
}

TEST(PeriodicTaskTest, SetInterval) {
    // Check that the interval can be set and retrieved correctly
    std::function<void(std::shared_ptr<Packet>&)> func =
        [](std::shared_ptr<Packet>& packet) {};
    PeriodicTask task(0, func);
    task.setInterval(1000);
    EXPECT_EQ(task.getInterval(), 1000);
}

TEST(PeriodicTaskTest, Execute) {
    // Check that the task is executed and the last_executed_time_ is updated
    // correctly
    std::function<void(std::shared_ptr<Packet>&)> func =
        [](std::shared_ptr<Packet>& packet) {};
    PeriodicTask task(0, func);
    std::shared_ptr<Packet> packet = std::make_shared<Packet>();
    auto now = std::chrono::steady_clock::now();
    task.execute(packet);
    auto last_executed_time = task.getLastExecutedTime();
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(
        last_executed_time - now);
    EXPECT_LE(diff.count(), 1);
}

TEST(PeriodicTaskTest, IsTimeToExecute) {
    // Check that isTimeToExecute returns true if enough time has passed since
    // the last execution
    std::function<void(std::shared_ptr<Packet>&)> func =
        [](std::shared_ptr<Packet>& packet) {};
    PeriodicTask task(1000, func);
    std::shared_ptr<Packet> packet = std::make_shared<Packet>();
    task.execute(packet);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    EXPECT_FALSE(task.isTimeToExecute());
    std::this_thread::sleep_for(std::chrono::milliseconds(600));
    EXPECT_TRUE(task.isTimeToExecute());
}