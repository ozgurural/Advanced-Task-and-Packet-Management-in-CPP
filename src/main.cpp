//  main.cpp

#include "TaskManager.h"
#include <iostream>
#include <memory>   

int main() {

    // Get a reference to the TaskManager instance.
    auto& task_manager = TaskManager::getInstance();

    // Start all tasks
    task_manager.startAllTasks();

    // Run the tasks until the user presses Enter
    std::cout << "Press Enter to stop the tasks..." << std::endl;
    std::cin.get();

    // Stop all tasks
    task_manager.stopAllTasks();

    return 0;
}
