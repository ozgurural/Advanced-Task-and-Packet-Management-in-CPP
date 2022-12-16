#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <condition_variable>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include "Logger.h"
#include "Packet.h"
#include "PeriodicTaskFactory.h"

class TaskManager {
public:
    static std::chrono::time_point<std::chrono::steady_clock> getTimeSource();

    void addTask(std::unique_ptr<PeriodicTask>);
    void removeTask(PeriodicTask task);
    void setPeriodicTaskInterval(PeriodicTask& task, int interval_sec);

    void addPacket(std::unique_ptr<Packet> pkt);

    void startAllTasks();
    void stopAllTasks();
    void onNewTime(struct timeval aCurrentTime);
    void processPackets();
    auto& getPacketsAndTasks() { return packets_and_tasks_map_; }
    timeval getCurrentTime() { return currentTime_; }

private:
    // current time
    timeval currentTime_ = {0, 0};

    // Mutex for thread-safety
    std::mutex mutex_;
    std::mutex packet_queue_mutex_;

    // Thread used to execute periodic tasks
    std::thread task_thread_;
    std::thread packet_thread_;

    // Map containing managed periodic tasks and Packages
    std::map<time_t,
             std::pair<std::vector<std::unique_ptr<Packet>>,
                       std::vector<std::unique_ptr<PeriodicTask>>>>
        packets_and_tasks_map_;

    // Queue of packets to be processed
    std::queue<std::unique_ptr<Packet>> incoming_packet_queue_;

    // Condition variable used to signal the task thread to wake up
    std::condition_variable packet_queue_cv_;

    void taskThreadFunc();
};

#endif  // TASK_MANAGER_H