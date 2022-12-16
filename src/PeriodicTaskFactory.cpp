// PeriodicTaskFactory.cpp

#include "PeriodicTaskFactory.h"

std::unique_ptr<PeriodicTaskFactory>
    PeriodicTaskFactory::periodicTaskFactoryInstance;

std::shared_ptr<PeriodicTask> PeriodicTaskFactory::createPeriodicTask(
    int interval,
    const std::function<void(std::shared_ptr<Packet>&)>& task) {
    return std::make_shared<PeriodicTask>(interval, task);
}
