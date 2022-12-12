#ifndef PERIODIC_TASK_FACTORY_H
#define PERIODIC_TASK_FACTORY_H

#include <chrono>
#include <map>
#include <mutex>
#include <memory>
#include <functional>

#include "PeriodicTask.h"

class PeriodicTaskFactory {
public:
    // Get a reference to the TaskManager instance.
    static PeriodicTaskFactory& getInstance() {
        // If the instance hasn't been created yet, create it.
        if (!periodicTaskFactoryInstance) {
            periodicTaskFactoryInstance = std::unique_ptr<PeriodicTaskFactory>(new PeriodicTaskFactory());
        }

        // Return a reference to the instance.
        return *periodicTaskFactoryInstance;
    }

    static std::unique_ptr<PeriodicTask> createPeriodicTask(int interval, const std::function<void()>& task);

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
    static std::unique_ptr<PeriodicTaskFactory> periodicTaskFactoryInstance;

    // Mutex for thread-safety
    std::mutex mutex_;

    // Variable to store the last time a task was executed
    std::chrono::time_point<std::chrono::system_clock> last_executed_time_;
    double interval_;
    std::function<void()> task_;
};

static std::unique_ptr<PeriodicTaskFactory> periodicTaskFactoryInstance;

#endif // PERIODIC_TASK_FACTORY_H