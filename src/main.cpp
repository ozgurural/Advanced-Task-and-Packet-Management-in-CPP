//  main.cpp

#include <iostream>
#include <memory>

#include "TaskManager.h"

int main() {
    // Create an object of type TaskManager
    TaskManager task_manager;

    // Start all tasks
    task_manager.startAllTasks();

    // Run the tasks until the user presses Enter
    std::cout << "Press Enter to stop the tasks..." << std::endl;
    std::cin.get();

    // Stop all tasks
    task_manager.stopAllTasks();

    return 0;
}
