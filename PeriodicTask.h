#pragma once

#include <chrono>
#include <map>
#include <mutex>
#include <functional>

class PeriodicTask {
public:
    // Adds a new periodic task with the given interval (in seconds) and function.
    // The function should be a callable object that takes no arguments and returns void.
    void Add(double interval, const std::function<void()>& func);

    // Removes a periodic task with the given interval (in seconds).
    // If no such task exists, this function has no effect.
    void Remove(double interval);

    // Changes the interval of a periodic task.
    // If no such task exists, this function has no effect.
    void ChangeInterval(double oldInterval, double newInterval);

    // Changes the interval of a periodic task.
    // If no such task exists and createIfNotExist is true,
    // a new task with the given interval and function is added.
    // If no such task exists and createIfNotExist is false, this function has no effect.
    void setInterval(double interval, const std::function<void()>& func, bool createIfNotExist = true);

    // Calls the correct periodic tasks based on the provided time (in seconds).
    void onNewTime(double time);

private:
    // Map of intervals (in seconds) to periodic task functions
    std::map<double, std::function<void()>> tasks_;

    // Mutex for thread-safety
    std::mutex mutex_;
};