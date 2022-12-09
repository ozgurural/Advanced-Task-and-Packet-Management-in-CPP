//
// Created by ozgurural on 12/8/22.
//

#include "TaskManager.h"

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
    tasks_.remove(task);
}

void TaskManager::setInterval(PeriodicTask task, int interval_sec) {
    std::lock_guard<std::mutex> lock(mutex_);

    std::function<void()> func = []() {
    // Your code here
    };
    bool createIfNotExist = true;


    task.setInterval(interval_sec, func, createIfNotExist);
}

void TaskManager::taskThreadFunc() {
    while (true) {
        // Use the time source function to get the current time.
        std::chrono::time_point<std::chrono::system_clock> now = time_source_();
        std::lock_guard<std::mutex> lock(mutex_);
        for (PeriodicTask& task : tasks_) {
            // Compute the elapsed time since the last execution of the task
            auto elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>(now - task.last_executed_time());

            // Convert the interval to a duration with the same units as elapsed_time
            auto interval = std::chrono::duration_cast<decltype(elapsed_time)>(
                std::chrono::duration<double>(task.interval())
            );


            // Check if the task needs to be executed
            if (elapsed_time >= interval) {
                // Execute the task and update the last_executed_time
                task.execute();
                task.set_last_executed_time(now);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}