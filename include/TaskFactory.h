#ifndef PERIODIC_TASK_FACTORY_H
#define PERIODIC_TASK_FACTORY_H

#include <memory>

#include "PeriodicTask.h"

// The factory class
class PeriodicTaskFactory {
public:
  // The factory method that creates PeriodicTask objects
  static std::unique_ptr<PeriodicTask> createPeriodicTask(int interval);
};

#endif // PERIODIC_TASK_FACTORY_H
