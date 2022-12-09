#include "PeriodicTask.h"

// Adds a new periodic task with the given interval (in seconds) and function.
// The function should be a callable object that takes no arguments and returns void.
void PeriodicTask::Add(double interval, const std::function<void()>& func)
{
    std::lock_guard<std::mutex> lock(*mutex_);
    tasks_[interval] = func;
}

// Removes a periodic task with the given interval (in seconds).
// If no such task exists, this function has no effect.
void PeriodicTask::Remove(double interval)
{
    std::lock_guard<std::mutex> lock(*mutex_);
    tasks_.erase(interval);
}

// Changes the interval of a periodic task.
// If no such task exists, this function has no effect.
void PeriodicTask::ChangeInterval(double oldInterval, double newInterval)
{
    std::lock_guard<std::mutex> lock(*mutex_);
    auto it = tasks_.find(oldInterval);
    if (it != tasks_.end())
    {
        tasks_[newInterval] = it->second;
        tasks_.erase(it);
    }
}

// Changes the interval of a periodic task.
// If no such task exists and createIfNotExist is true,
// a new task with the given interval and function is added.
// If no such task exists and createIfNotExist is false, this function has no effect.
void PeriodicTask::setInterval(double interval, const std::function<void()>& func, bool createIfNotExist) {
    std::lock_guard<std::mutex> lock(*mutex_);
    auto it = tasks_.find(interval);
    if (it != tasks_.end()) {
        // Update the existing task
        tasks_[interval] = func;
    } else if (createIfNotExist) {
        // Add a new task with the given interval and function
        tasks_[interval] = func;
    }
}

// Calls the correct periodic tasks based on the provided time (in seconds).
void PeriodicTask::onNewTime(double time) {
    std::lock_guard<std::mutex> lock(*mutex_);
    // Check if any tasks need to be executed at the current time
    auto it = tasks_.lower_bound(time);
    while (it != tasks_.end() && it->first == time) {
        // Execute the task and advance the iterator
        it->second();
        ++it;
    }
}
