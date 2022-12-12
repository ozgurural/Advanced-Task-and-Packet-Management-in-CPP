#include "PeriodicTask.h"

void PeriodicTask::setInterval(double interval, const std::function<void()>& func) {
    std::lock_guard<std::mutex> lock(mutex_);
}

void PeriodicTask::execute() {
    
}

void PeriodicTask::setLastExecutedTime(std::chrono::time_point<std::chrono::system_clock> point) {
    std::lock_guard<std::mutex> lock(mutex_);
    last_executed_time_ = point;
}