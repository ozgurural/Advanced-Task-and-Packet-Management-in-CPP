#include <list>
#include "PeriodicTask.h"

class TaskManager {
public:
    // Returns the singleton instance of the task manager.
    static TaskManager* getInstance();

    // Constructs the task manager with the given time source.
    TaskManager(std::function<std::chrono::time_point<std::chrono::system_clock>()> time_source);

    // Adds a new task to the list of periodic tasks.
    void addTask(PeriodicTask task);

    // Removes a task from the list of periodic tasks.
    void removeTask(PeriodicTask task);

    // Changes the interval of a task.
    void setInterval(PeriodicTask task, int interval_sec);

private:
    // Private constructor to enforce singleton pattern.
    TaskManager() {}

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
