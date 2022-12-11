#include "PeriodicTask.h"

// Changes the interval of a periodic task.
// If no such task exists and createIfNotExist is true,
// a new task with the given interval and function is added.
// If no such task exists and createIfNotExist is false, this function has no effect.
void PeriodicTask::setInterval(double interval, const std::function<void()>& func) {
    std::lock_guard<std::mutex> lock(mutex_);

}

// Calls the correct periodic tasks based on the provided time (in seconds).
void PeriodicTask::onNewTime(double time) {
    std::lock_guard<std::mutex> lock(mutex_);
    // Convert the time to seconds
    auto timeInSeconds = time / (24 * 60 * 60);
    // Check if any tasks need to be executed at the current time
    auto it = tasks_.lower_bound(timeInSeconds);
    while (it != tasks_.end() && it->first == timeInSeconds) {
        // Execute the task and advance the iterator
        it->second();
        ++it;
    }
}

void PeriodicTask::execute() {
    
}
