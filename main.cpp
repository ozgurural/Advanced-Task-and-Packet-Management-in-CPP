#include <iostream>
#include <chrono>
#include "TaskManager.h"
#include "PeriodicTask.h"

/*
 * In this example, the TaskManager instance is created with the getTime function as the time source.
 * This function simply returns the current time from the system clock.
 * The TaskManager instance is then used to add a periodic task that prints "Hello, world!" to the console every 5 seconds.
 * Because the TaskManager uses the getTime function as its time source,
 * the task will be executed at the correct intervals, based on the time returned by the getTime function.
 *
 */
// Function that returns the current time.
std::chrono::time_point<std::chrono::system_clock> getTime() {
    // Return the current time.
    return std::chrono::system_clock::now();
}
/*
void onNewTime(struct timeval aCurrentTime ) {
    currentTime = aCurrentTime;

    <your interface instance>.onNewTime(aCurrentTime);
}


void processPackets() {
    while (true) {
        //Get the latest packet (from online or offline source)
        pkt = pop_packet();

        // Only call onNewTime when second-part has changed, for efficiency
        //
        if(currentTime.tv_sec != pkt.tv_sec ) {
            onNewTime(pkt.time);
        }

        process_pkt(pkt);
    }
}
*/
int main() {
    // Create a task manager instance with the getTime function as the time source.
    TaskManager* task_manager = new TaskManager(getTime);

    // Create a periodic task that prints "Hello, world!" to the console every 5 seconds.
    PeriodicTask task([&]() {
        std::cout << "Hello, world!" << std::endl;
    }, 5);

    // Add the task to the task manager.
    task_manager->addTask(task);


    return 0;
}
