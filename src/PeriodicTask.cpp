#include "PeriodicTask.h"

// initialize the static next_id_ variable
int PeriodicTask::next_id_ = 0;

void PeriodicTask::setLastExecutedTime(
    std::chrono::time_point<std::chrono::steady_clock> point) {
    std::lock_guard<std::mutex> lock(mutex_);
    last_executed_time_ = point;
}

void PeriodicTask::setInterval(long interval) {
    std::lock_guard<std::mutex> lock(mutex_);
    interval_ = interval;
}

void PeriodicTask::setFunction(
    const std::function<void(std::shared_ptr<Packet>&)>& func) {
    std::lock_guard<std::mutex> lock(mutex_);
    task_ = func;
}

void PeriodicTask::execute(std::shared_ptr<Packet>& packet) {
    std::lock_guard<std::mutex> lock(mutex_);
    task_(packet);
    last_executed_time_ = std::chrono::steady_clock::now();
}

bool PeriodicTask::isTimeToExecute() {
    std::lock_guard<std::mutex> lock(mutex_);
    auto now = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(
        now - last_executed_time_);
    return diff.count() >= interval_;
}

std::function<void(std::shared_ptr<Packet>&)> PeriodicTask::getFunction() {
    std::lock_guard<std::mutex> lock(mutex_);
    return task_;
}
