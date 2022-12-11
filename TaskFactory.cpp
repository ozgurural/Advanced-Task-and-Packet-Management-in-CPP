#include "TaskFactory.h"
#include <iostream>

// The factory class
class PeriodicTaskFactory {
public:
  // The factory method that creates PeriodicTask objects
  static std::unique_ptr<PeriodicTask> createPeriodicTask(int interval) {
    // You can also use the std::chrono::seconds function to create a duration
    auto task = std::make_unique<PeriodicTask> (
        []() {
            std::cout << "Hello, world!" << std::endl;
        },
        interval
    );
    
    return std::make_unique<PeriodicTask>(task);
  }
};
