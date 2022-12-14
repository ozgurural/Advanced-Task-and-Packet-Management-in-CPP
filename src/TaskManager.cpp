#include "TaskManager.h"

// Define the time_source_() function.
std::chrono::time_point<std::chrono::steady_clock>
TaskManager::getTimeSource() {
    // Return the current time according to a monotonic clock.
    return std::chrono::steady_clock::now();
}

// Method to process packets from the current source until there are no more
// packets.
void TaskManager::processPackets() {
    while (true) {
        // Wait for the next packet to be available in the queue
        std::unique_lock<std::mutex> lock(packet_queue_mutex_);
        packet_queue_cv_.wait(
            lock, [this] { return !incoming_packet_queue_.empty(); });

        // Pop the next packet from the queue
        auto packet = *incoming_packet_queue_.front();
        incoming_packet_queue_.pop();
        lock.unlock();

        // If the packet has a new timestamp, call onNewTime()
        if (currentTime_.tv_sec != packet.time.tv_sec) {
            onNewTime(packet.time);
        }

        // Add packet to the packets_and_tasks_map_
        addPacket(std::make_unique<Packet>(packet));
    }
}

void TaskManager::addPacket(std::unique_ptr<Packet> packet) {
    std::lock_guard<std::mutex> lock(packet_queue_mutex_);
    packets_and_tasks_map_[packet.get()->time.tv_sec].first.emplace_back(
        std::move(packet));
    packet_queue_cv_.notify_one();
}

void TaskManager::onNewTime(struct timeval aCurrentTime) {
    std::lock_guard<std::mutex> lock(mutex_);
    currentTime_ = aCurrentTime;

    // Update the PeriodicTask objects in the TaskManager
    // TaskManager::getInstance().setInterval(PeriodicTask, aCurrentTime);
}

// Initialize the static instance variable.
std::unique_ptr<TaskManager> TaskManager::taskManagerInstance;

void TaskManager::addTask(std::unique_ptr<PeriodicTask> task) {
    std::lock_guard<std::mutex> lock(mutex_);

    auto interval = task->getInterval();

    packets_and_tasks_map_[interval].second.emplace_back(std::move(task));
}

void TaskManager::removeTask(PeriodicTask task) {
    std::lock_guard<std::mutex> lock(mutex_);

    // tasks_ is a map from interval to vector of tasks
    // get the vector of tasks for the given interval
    auto& task_vec = packets_and_tasks_map_[task.getInterval()].second;

    // find the task with the matching id and remove it
    task_vec.erase(
        std::remove_if(task_vec.begin(), task_vec.end(),
                       [&task](const std::unique_ptr<PeriodicTask>& t) {
                           return t->getId() == task.getId();
                       }),
        task_vec.end());
}

void TaskManager::setInterval(PeriodicTask& task, int interval_sec) {
    std::lock_guard<std::mutex> lock(mutex_);

    // Update the task interval
    task.setInterval(interval_sec);
}

void TaskManager::startAllTasks() {
    task_thread_ = std::thread(&TaskManager::taskThreadFunc, this);
    packet_thread_ = std::thread(&TaskManager::processPackets, this);
}

void TaskManager::stopAllTasks() {
    task_thread_.join();
    packet_thread_.join();
}

void TaskManager::taskThreadFunc() {
    while (true) {
        // Use the time source function to get the current time.
        std::chrono::time_point<std::chrono::steady_clock> now =
            getTimeSource();
        std::lock_guard<std::mutex> lock(mutex_);

        // std::map<time_t, std::pair<std::vector<std::unique_ptr<Packet>>,
        // std::vector<std::unique_ptr<PeriodicTask>>>> packets_and_tasks_map_;
        // Create a duration that represents the interval in seconds
        auto interval = std::chrono::duration<double>(currentTime_.tv_sec);
        auto& packets_and_tasks = packets_and_tasks_map_[currentTime_.tv_sec];

        // Iterate over the vector of tasks
        for (auto& task : packets_and_tasks.second) {
            // Compute the elapsed time since the last execution of the task
            auto elapsed_time =
                std::chrono::duration_cast<std::chrono::duration<double>>(
                    now - task->getLastExecutedTime());

            // Check if the task needs to be executed
            if (elapsed_time >= interval) {
                // Iterate over the packets and execute the task with each
                // packet
                for (auto& packet : packets_and_tasks.first) {
                    task->execute(packet);
                }
                // Update the last_executed_time
                task->setLastExecutedTime(now);
            }
        }

        // Sleep for a short time to allow other threads to run
        // @todo - make this time configurable or use a condition variable
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
