#include "TaskManager.h"
#include "PeriodicTask.h"
#include <iostream>


// Function that returns the current time.
std::chrono::time_point<std::chrono::system_clock> getTime() {
    // Return the current time.
    return std::chrono::system_clock::now();
}

struct timeval currentTime;

void onNewTime(struct timeval aCurrentTime ) {
    currentTime = aCurrentTime;

    // Update the PeriodicTask objects in the TaskManager
    TaskManager::getInstance().onNewTime(aCurrentTime);
}

void processPackets() {
    while (true) {
        // Get the latest packet (from online or offline source)
        pkt = pop_packet();

        // Only call onNewTime when second-part has changed, for efficiency
        //
        if(currentTime.tv_sec != pkt.tv_sec ) {
            onNewTime(pkt.time);
        }

        process_pkt(pkt);
    }
}


int main() {
    // Create a task manager instance with the getTime function as the time source.
    TaskManager* task_manager = new TaskManager(getTime);

    // Create a periodic task that prints "Hello, world!" every second
    auto task1 = std::make_unique<PeriodicTask>(
        "Hello, world!",
        std::chrono::seconds(1),
        []() {
        std::cout << "Hello, world!" << std::endl;
        }
    );

    // Add the task to the task manager.
    task_manager->addTask(std::move(task1));

    // Start all tasks
    task_manager.startAllTasks();

    // Run the tasks until the user presses Enter
    std::cout << "Press Enter to stop the tasks..." << std::endl;
    std::cin.get();

    // Stop all tasks
    task_manager.stopAllTasks();



    return 0;
}
