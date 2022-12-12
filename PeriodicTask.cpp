#include "PeriodicTask.h"

void PeriodicTask::setInterval(double interval, const std::function<void()>& func) {
    std::lock_guard<std::mutex> lock(mutex_);
}

void PeriodicTask::execute() {
    
}
