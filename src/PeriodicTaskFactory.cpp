// PeriodicTaskFactory.cpp

#include "PeriodicTaskFactory.h"

std::unique_ptr<PeriodicTaskFactory>
    PeriodicTaskFactory::periodicTaskFactoryInstance;
std::unique_ptr<PeriodicTask> PeriodicTaskFactory::createPeriodicTask(
    int interval,
    const std::function<void(std::unique_ptr<Packet>&)>& task) {
    return std::make_unique<PeriodicTask>(interval, task);
}