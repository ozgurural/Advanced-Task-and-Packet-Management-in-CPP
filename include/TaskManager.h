#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <condition_variable>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include "Packet.h"
#include "PeriodicTaskFactory.h"

class TaskManager {
public:
    // Private copy constructor and assignment operator.
    TaskManager(const TaskManager&) = delete;
    TaskManager& operator=(const TaskManager&) = delete;

    // Get a reference to the TaskManager instance.
    static TaskManager& getInstance() {
        // If the instance hasn't been created yet, create it.
        if (!taskManagerInstance) {
            taskManagerInstance =
                std::unique_ptr<TaskManager>(new TaskManager());
        }

        // Return a reference to the instance.
        return *taskManagerInstance;
    }

    std::chrono::time_point<std::chrono::steady_clock> getTimeSource();
    void addTask();
    std::map<int, std::vector<std::unique_ptr<PeriodicTask>>>& getTasks();
    void removeTask(PeriodicTask task);
    void setInterval(PeriodicTask& task, int interval_sec);
    void startAllTasks();
    void stopAllTasks();
    void onNewTime(auto PeriodicTask, struct timeval aCurrentTime);
    void processPackets();
    void addPacket(Packet pkt);

private:
    // Private constructor.
    TaskManager() = default;

    // current time
    timeval currentTime_;

    // Private static member variable to store the instance.
    static std::unique_ptr<TaskManager> taskManagerInstance;

    // Mutex for thread-safety
    std::mutex mutex_;
    std::mutex packet_queue_mutex_;

    // Thread used to execute periodic tasks
    std::thread task_thread_;
    std::thread packet_thread_;

    // Map containing managed periodic tasks
    std::map<time_t, std::vector<std::unique_ptr<PeriodicTask>>> tasks_;

    // Queue of packets to be processed
    std::queue<std::unique_ptr<Packet>> packet_queue_;

    // Condition variable used to signal the task thread to wake up
    std::condition_variable packet_queue_cv_;

    void taskThreadFunc();
};

#endif  // TASK_MANAGER_H