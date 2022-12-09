#include <list>
#include <mutex>
#include <thread>
#include "PeriodicTask.h"

class TaskManager {
public:
    // Get a reference to the TaskManager instance.
    static TaskManager& getInstance() {
        // If the instance hasn't been created yet, create it.
        if (!instance) {
            instance = std::unique_ptr<TaskManager>(new TaskManager());
        }

        // Return a reference to the instance.
        return *instance;
    }

    // Adds a new task to the list of periodic tasks.
    void addTask(PeriodicTask task);

    // Removes a task from the list of periodic tasks.
    void removeTask(PeriodicTask task);

    // Changes the interval of a task.
    void setInterval(PeriodicTask task, int interval_sec);

    void startAllTasks();

    void stopAllTasks();

private:
    // Private constructor.
    TaskManager() {}

    // Private copy constructor and assignment operator.
    TaskManager(const TaskManager&) = delete;
    TaskManager& operator=(const TaskManager&) = delete;

    // Private static member variable to store the instance.
    static std::unique_ptr<TaskManager> instance;

    // Thread function that periodically checks the list of tasks and
    // executes any tasks that are due to be run.
    void taskThreadFunc();

    // Function that returns the current time.
    std::function<std::chrono::time_point<std::chrono::system_clock>()> time_source_;

    // List of periodic tasks.
    std::list<PeriodicTask> tasks_;

    // Mutex to ensure thread-safety.
    std::mutex mutex_;

    // Thread that runs the taskThreadFunc function.
    std::thread task_thread_;
};

// Initialize the static instance variable.
std::unique_ptr<TaskManager> TaskManager::instance;