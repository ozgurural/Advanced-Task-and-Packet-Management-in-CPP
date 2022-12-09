    //  main.cpp

    #include "TaskManager.h"
    #include "PeriodicTask.h"
    #include <iostream>
    #include <memory>   
    #include <pcap/pcap.h>  


    int currentTime = 0;


    // Method to retrieve the next packet from the current source.
    // This method returns a data structure that contains the packet header and data.
    pcap_pkthdr* pop_packet()
    {
        // Open the PCAP file.
        pcap_t* handle = pcap_open_offline("packets.pcap", nullptr);

        // Define a buffer to hold the packet data.
        const u_char* packet_data;

        // Define a header to hold the packet header information.
        pcap_pkthdr* packet_header;

        // Retrieve the next packet from the PCAP file.
        int result = pcap_next_ex(handle, &packet_header, &packet_data);

        // If a packet was successfully retrieved, return the header and data.
        // Otherwise, return nullptr.
        if (result == 1)
        {
            return packet_header;
        }
        else
        {
            return nullptr;
        }
    }

    // Method to process a packet.
    void process_pkt(const pcap_pkthdr* packet_header, const u_char* packet_data)
    {
        // Print some information about the packet to the console.
        std::cout << "Packet length: " << packet_header->len << std::endl;
        std::cout << "Packet timestamp: " << packet_header->ts.tv_sec << "." << packet_header->ts.tv_usec << std::endl;
        std::cout << "Packet data: " << packet_data << std::endl;
    }

    // Method to process packets from the current source until there are no more packets.
    void processPackets() {
        // Define a packet header to hold the packet header information.
        pcap_pkthdr* packet_header;

        // Define a buffer to hold the packet data.
        const u_char* packet_data;

        // Process packets until there are no more packets in the current source.
        while (true) {
            // Retrieve the next packet from the current source.
            packet_header = pop_packet();

            // If there are no more packets, exit the loop.
            if (packet_header == nullptr) {
                break;
            }

            // Process the packet.
            process_pkt(packet_header, packet_data);
        }
    }

    void onNewTime(auto PeriodicTask, struct timeval aCurrentTime ) {
        currentTime = aCurrentTime;

        // Update the PeriodicTask objects in the TaskManager
        TaskManager::getInstance().setInterval(PeriodicTask, aCurrentTime);
    }

    int main() {
        
        // Get a reference to the TaskManager instance.
        auto& task_manager = TaskManager::getInstance();

        // Create a periodic task that prints "Hello, world!" every second
        auto task1 = std::make_unique<PeriodicTask>(
            "Hello, world!",
            std::chrono::seconds(1),
            []() {
            std::cout << "Hello, world!" << std::endl;
            }
        );

        // Add the task to the task manager.
        task_manager.addTask(*task1);

        // Start all tasks
        task_manager.startAllTasks();

        // Run the tasks until the user presses Enter
        std::cout << "Press Enter to stop the tasks..." << std::endl;
        std::cin.get();

        // Stop all tasks
        task_manager.stopAllTasks();

        return 0;
    }
