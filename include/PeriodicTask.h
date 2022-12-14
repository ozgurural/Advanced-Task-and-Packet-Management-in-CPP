#ifndef PERIODIC_TASK_H
#define PERIODIC_TASK_H

#include <chrono>
#include <functional>
#include <map>
#include <mutex>

class PeriodicTask {
public:
    // Constructor that takes a lambda function and an integer as arguments
    PeriodicTask(double interval, const std::function<void()>& task)
        : last_executed_time_(std::chrono::steady_clock::now()),
          task_(task),
          interval_(0),
          func_(task),
          id_(next_id_++) {}

    // get the unique id of the task
    int getId() const { return id_; }

    auto getLastExecutedTime() const { return last_executed_time_; }

    // Changes the interval of a periodic task.
    void setInterval(double interval);

    auto getInterval() const { return interval_; }

    void setFunction(const std::function<void()>& func);

    bool isTimeToExecute();

    void execute();

    void setLastExecutedTime(
        std::chrono::time_point<std::chrono::steady_clock> point);

private:
    // unique id of the task
    int id_;

    // static variable to keep track of the last assigned id
    static int next_id_;

    // periodic task
    const std::function<void()>& task_;

    // Mutex for thread-safety
    std::mutex mutex_;

    // Variable to store the last time a task was executed
    std::chrono::time_point<std::chrono::steady_clock> last_executed_time_;
    double interval_;
    std::function<void()> func_ = nullptr;
};

#endif  // PERIODIC_TASK_H