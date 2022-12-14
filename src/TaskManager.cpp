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
        packet_queue_cv_.wait(lock, [this] { return !incoming_packet_queue_.empty(); });

        // Pop the next packet from the queue
        auto pkt = incoming_packet_queue_.front();
        incoming_packet_queue_.pop();
        lock.unlock();

        // If the packet has a new timestamp, call onNewTime()
        if (currentTime_.tv_sec != pkt.time.tv_sec) {
            onNewTime(pkt.time);
        }

        // Process the packet.
        process_pkt(pkt);
    }
}

void TaskManager::addPacket(Packet pkt) {
    std::lock_guard<std::mutex> lock(packet_queue_mutex_);
    packet_queue_.push(pkt);
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

void TaskManager::addTask() {
    std::lock_guard<std::mutex> lock(mutex_);

    auto& task_factory = PeriodicTaskFactory::getInstance();

    std::unique_ptr<PeriodicTask> task =
        task_factory.createPeriodicTask(1, []() {
            // Your code here
        });

    auto interval = task->getInterval();
    tasks_[interval].emplace_back(std::move(task));
}

// std::map<int, std::vector<std::unique_ptr<PeriodicTask>>> tasks_;
std::map<time_t, std::vector<std::unique_ptr<PeriodicTask>>>&
TaskManager::getTasks() {
    std::lock_guard<std::mutex> lock(mutex_);
    return tasks_;
}

void TaskManager::removeTask(PeriodicTask task) {
    std::lock_guard<std::mutex> lock(mutex_);

    // tasks_ is a map from interval to vector of tasks
    // get the vector of tasks for the given interval
    auto& task_vec = tasks_[task.getInterval()];

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

        // std::map<time_t, std::vector<std::unique_ptr<PeriodicTask>>> tasks_;
        auto& interval = currentTime_.tv_sec;
        auto& currentTime_tasks = tasks_[currentTime_.tv_sec];
        // Iterate over the vector of tasks
        for (auto& task : currentTime_tasks) {
            // Compute the elapsed time since the last execution of the task
            auto elapsed_time =
                std::chrono::duration_cast<std::chrono::duration<double>>(
                    now - task->getLastExecutedTime());

            // Convert the interval to a duration with the same units as
            // elapsed_time
            auto interval_duration =
                std::chrono::duration_cast<decltype(elapsed_time)>(
                    std::chrono::duration<double>(interval));

            // Check if the task needs to be executed
            if (elapsed_time >= interval_duration) {
                // Execute the task and update the last_executed_time
                task->execute();
                task->setLastExecutedTime(now);
            }
        }
        // Sleep for a short time to allow other threads to run
        // @todo - make this time configurable or use a condition variable
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
