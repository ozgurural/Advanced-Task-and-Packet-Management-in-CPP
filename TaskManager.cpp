//
// Created by ozgurural on 12/8/22.
//

#include "TaskManager.h"
#include "PeriodicTaskFactory.h"

void TaskManager::addTask() {
    std::lock_guard<std::mutex> lock(mutex_);

    std::unique_ptr<PeriodicTask> task = PeriodicTaskFactory::createPeriodicTask(1);
    // Add the task to the list of managed tasks
    tasks_.emplace(task->getId(), std::move(task));
}

void TaskManager::removeTask(PeriodicTask task) {
    std::lock_guard<std::mutex> lock(mutex_);
    tasks_.erase(0);
}

void TaskManager::setInterval(PeriodicTask& task, int interval_sec) {
    std::lock_guard<std::mutex> lock(mutex_);

    // Define the task function
    std::function<void()> func = []() {
        // Your code here
    };

    // Update the task interval
    task.setInterval(interval_sec, func);
}


void TaskManager::startAllTasks() {
    task_thread_ = std::thread(&TaskManager::taskThreadFunc, this);
}

void TaskManager::stopAllTasks() {
    task_thread_.join();
}


void TaskManager::taskThreadFunc() {
    while (true) {
        // Use the time source function to get the current time.
        /*
        std::chrono::time_point<std::chrono::system_clock> now = time_source_();
        std::lock_guard<std::mutex> lock(mutex_);
        for (PeriodicTask &task(<#initializer#>, 0, <#initializer#>): tasks_) {
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
        */
    }
}