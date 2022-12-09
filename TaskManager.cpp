//
// Created by ozgurural on 12/8/22.
//

#include <mutex>
#include <thread>
#include <list>
#include "TaskManager.h"

using namespace std;

TaskManager* TaskManager::getInstance() {
    static TaskManager instance;
    return &instance;
}

TaskManager::TaskManager(std::function<std::chrono::time_point<std::chrono::system_clock>()> time_source)
        : time_source_(time_source) {}

void TaskManager::addTask(PeriodicTask task) {
    std::lock_guard<std::mutex> lock(mutex_);
    tasks_.push_back(task);
}

void TaskManager::removeTask(PeriodicTask task) {
    std::lock_guard<std::mutex> lock(mutex_);
    tasks_.Remove(task);
}

void TaskManager::setInterval(PeriodicTask task, int interval_sec) {
    std::lock_guard<std::mutex> lock(mutex_);
    task.setInterval(interval_sec);
}

void TaskManager::taskThreadFunc() {
    while (true) {
        // Use the time source function to get the current time.
        std::chrono::time_point<std::chrono::system_clock> now = time_source_();
        std::lock_guard<std::mutex> lock(mutex_);
        for (PeriodicTask& task : tasks_) {
            if (now - task.last_executed_time() >= task.interval()) {
                task.execute();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}