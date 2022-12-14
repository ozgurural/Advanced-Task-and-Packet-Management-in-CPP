#ifndef PERIODIC_TASK_FACTORY_H
#define PERIODIC_TASK_FACTORY_H

#include <chrono>
#include <functional>
#include <map>
#include <memory>
#include <mutex>

#include "PeriodicTask.h"

class PeriodicTaskFactory {
public:
    // Private copy constructor and assignment operator.
    PeriodicTaskFactory(const PeriodicTaskFactory&) = delete;
    PeriodicTaskFactory& operator=(const PeriodicTaskFactory&) = delete;

    // Get a reference to the TaskManager instance.
    static PeriodicTaskFactory& getInstance() {
        // If the instance hasn't been created yet, create it.
        if (!periodicTaskFactoryInstance) {
            periodicTaskFactoryInstance =
                std::unique_ptr<PeriodicTaskFactory>(new PeriodicTaskFactory());
        }

        // Return a reference to the instance.
        return *periodicTaskFactoryInstance;
    }

    static std::unique_ptr<PeriodicTask> createPeriodicTask(
        int interval,
        const std::function<void(std::unique_ptr<Packet>&)>& task);

private:
    // Private constructor.
    PeriodicTaskFactory() = default;

    // Private static member variable to store the instance.
    static std::unique_ptr<PeriodicTaskFactory> periodicTaskFactoryInstance;
};

static std::unique_ptr<PeriodicTaskFactory> periodicTaskFactoryInstance;

#endif  // PERIODIC_TASK_FACTORY_H