#ifndef PERIODIC_TASK_H
#define PERIODIC_TASK_H

#include <chrono>
#include <functional>
#include <map>
#include <memory>
#include <mutex>

#include "Packet.h"

class PeriodicTask {
public:
    // Constructor that takes a lambda function and an integer as arguments
    PeriodicTask(long interval,
                 const std::function<void(std::unique_ptr<Packet>&)>& task)
        : last_executed_time_(std::chrono::steady_clock::now()),
          task_(task),
          interval_(interval),
          id_(next_id_++) {}

    // get the unique id of the task
    int getId() const { return id_; }

    std::chrono::time_point<std::chrono::steady_clock> getLastExecutedTime()
        const {
        return last_executed_time_;
    }

    // Changes the interval of a periodic task.
    void setInterval(double interval);

    auto getInterval() const { return interval_; }

    void setFunction(const std::function<void(std::unique_ptr<Packet>&)>& func);

    bool isTimeToExecute();

    void execute(std::unique_ptr<Packet>&);

    void setLastExecutedTime(
        std::chrono::time_point<std::chrono::steady_clock> point);

private:
    // unique id of the task
    int id_ = 0;

    // static variable to keep track of the last assigned id
    static int next_id_;

    // periodic task
    std::function<void(std::unique_ptr<Packet>&)> task_;

    // Mutex for thread-safety
    std::mutex mutex_;

    // Variable to store the last time a task was executed
    std::chrono::time_point<std::chrono::steady_clock> last_executed_time_;
    long interval_;
};

#endif  // PERIODIC_TASK_H