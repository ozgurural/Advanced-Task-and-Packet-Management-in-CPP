// PeriodicTaskFactory.cpp

#include "PeriodicTaskFactory.h"

std::unique_ptr<PeriodicTaskFactory>
    PeriodicTaskFactory::periodicTaskFactoryInstance;
std::unique_ptr<PeriodicTask> PeriodicTaskFactory::createPeriodicTask(
    int interval,
    const std::function<void()>& task) {
    return std::make_unique<PeriodicTask>(interval, task);
}