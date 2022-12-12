#ifndef PERIODIC_TASK_H
#define PERIODIC_TASK_H

#include <chrono>
#include <map>
#include <mutex>
#include <functional>

class PeriodicTask {
public:
    // Constructor that takes a lambda function and an integer as arguments
    PeriodicTask(double interval, const std::function<void()> &task)
            : last_executed_time_(std::chrono::system_clock::now()), task_(task), interval_(0) {
    }

    auto getLastExecutedTime() const { return last_executed_time_; }

    int getId() const { return id_; }

    // Changes the interval of a periodic task.
    void setInterval(double interval, const std::function<void()>& func);

    void execute();

    void setLastExecutedTime(std::chrono::time_point<std::chrono::system_clock> point);

private:
    // periodic task
    const std::function<void()>& task_;

    int id_ = 0;

    // Mutex for thread-safety
    std::mutex mutex_;

    // Variable to store the last time a task was executed
    std::chrono::time_point<std::chrono::system_clock> last_executed_time_;
    double interval_;
    
};

#endif // PERIODIC_TASK_H