#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <map>
#include <vector>
#include <mutex>
#include <memory>
#include <thread>

#include "PeriodicTaskFactory.h"

class TaskManager {
public:
    // Get a reference to the TaskManager instance.
    static TaskManager& getInstance() {
        // If the instance hasn't been created yet, create it.
        if (!taskManagerInstance) {
            taskManagerInstance = std::unique_ptr<TaskManager>(new TaskManager());
        }

        // Return a reference to the instance.
        return *taskManagerInstance;
    }

    void addTask();
    void removeTask(PeriodicTask task);
    void setInterval(PeriodicTask& task, int interval_sec);
    void startAllTasks();
    void stopAllTasks();

private:
    // Private constructor.
    TaskManager() {}

    // Private copy constructor and assignment operator.
    TaskManager(const TaskManager&) = delete;
    TaskManager& operator=(const TaskManager&) = delete;

    // Private static member variable to store the instance.
    static std::unique_ptr<TaskManager> taskManagerInstance;

    // Mutex for thread-safety
    std::mutex mutex_;

    // Thread used to execute periodic tasks
    std::thread task_thread_;

    // Map containing managed periodic tasks
    std::map<int, std::vector<std::unique_ptr<PeriodicTask>>> tasks_;

    void taskThreadFunc();
};


#endif // TASK_MANAGER_H