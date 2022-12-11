#include "PeriodicTask.h"

// Changes the interval of a periodic task.
// If no such task exists and createIfNotExist is true,
// a new task with the given interval and function is added.
// If no such task exists and createIfNotExist is false, this function has no effect.
void PeriodicTask::setInterval(double interval, const std::function<void()>& func) {
    std::lock_guard<std::mutex> lock(mutex_);

}

void PeriodicTask::execute() {
    
}
