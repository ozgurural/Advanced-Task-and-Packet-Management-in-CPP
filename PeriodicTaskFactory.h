#ifndef PERIODIC_TASK_FACTORY_H
#define PERIODIC_TASK_FACTORY_H

#include <chrono>
#include <map>
#include <mutex>
#include <functional>
#include <memory>

#include "PeriodicTask.h"

class PeriodicTaskFactory {
public:
    // Get a reference to the TaskManager instance.
    static PeriodicTaskFactory& getInstance() {
        // If the instance hasn't been created yet, create it.
        if (!instance) {
            instance = std::unique_ptr<PeriodicTaskFactory>(new PeriodicTaskFactory());
        }

        // Return a reference to the instance.
        return *instance;
    }

    static std::unique_ptr<PeriodicTask> createPeriodicTask(int interval);

    auto getLastExecutedTime() const { return last_executed_time_; }

    // Changes the interval of a periodic task.
    void setInterval(double interval, const std::function<void()>& func);

    void execute();

    void setLastExecutedTime(std::chrono::time_point<std::chrono::system_clock> point);

private:
    // Private constructor.
    PeriodicTaskFactory() {}

    // Private copy constructor and assignment operator.
    PeriodicTaskFactory(const PeriodicTaskFactory&) = delete;
    PeriodicTaskFactory& operator=(const PeriodicTaskFactory&) = delete;

    // Private static member variable to store the instance.
    static std::unique_ptr<PeriodicTaskFactory> instance;

    // Mutex for thread-safety
    std::mutex mutex_;

    // Variable to store the last time a task was executed
    std::chrono::time_point<std::chrono::system_clock> last_executed_time_;
    double interval_;
    
};

// Initialize the static instance variable.
std::unique_ptr<PeriodicTaskFactory> PeriodicTaskFactory::instance;

#endif // PERIODIC_TASK_FACTORY_H