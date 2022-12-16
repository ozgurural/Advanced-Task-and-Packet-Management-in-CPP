//  main.cpp

#include "Logger.h"
#include "TaskManager.h"

int main() {
    // Create an object of type TaskManager
    TaskManager task_manager;

    struct timeval packet_time = {1000, 0};
    std::vector<uint8_t> packet_data = {1, 2, 3, 4};
    std::shared_ptr<Packet> packet =
        std::make_shared<Packet>(packet_time, packet_data);

    // Add a packet to the queue.
    task_manager.addPacket(packet);

    LOG(INFO) << "Number of packets added from main:"
              << task_manager.getPacketsAndTasks()[packet->time.tv_sec]
                     .packets.size();

    std::map<time_t, PacketsAndTasks>& pt = task_manager.getPacketsAndTasks();
    // Check that the queue contains the expected packet.
    auto it = pt.begin();
    std::cout << it->first << ": ";
    for (auto& byte : it->second.packets.front()->data) {
        std::cout << std::hex << (int)byte << " ";
    }
    std::cout << std::endl;

    // Create a function that prints the packet data
    auto print_packet_data = [](std::shared_ptr<Packet>& packet) {
        std::cout << "Packet data: ";
        for (auto& byte : packet->data) {
            std::cout << std::hex << (int)byte << " ";
        }
        std::cout << std::endl;
    };

    // Create periodic tasks which take interval and packet as arguments and
    // print them periodically
    auto task1 = std::make_shared<PeriodicTask>(1000, print_packet_data);
    auto task2 = std::make_shared<PeriodicTask>(1000, print_packet_data);
    auto task3 = std::make_shared<PeriodicTask>(1000, print_packet_data);


    // Add the tasks to the task manager
    task_manager.addTask(std::move(task1));
    task_manager.addTask(std::move(task2));
    task_manager.addTask(std::move(task3));

    task_manager.onNewTime({1, 0});

    // Start all tasks
    task_manager.startAllTasks();

    // wait until enter is pressed
    std::cin.get();

    // Log Stop all tasks will be called from main
    LOG(INFO) << "Stop all tasks will be called from main";

    // Stop all tasks
    task_manager.stopAllTasks();

    return 0;
}
