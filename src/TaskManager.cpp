#include "TaskManager.h"

TaskManager::~TaskManager() {
    // Clean up resources and stop any threads
    stopAllTasks();
}

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
        // Log waiting for the next packet
        LOG(INFO) << "Waiting for the next packet";
        packet_queue_cv_.wait(
            lock, [this] { return !incoming_packet_queue_.empty() || stop_; });

        if (stop_) {
            return;
        }

        // Pop the next packet from the queue
        auto packet = std::move(incoming_packet_queue_.front());
        incoming_packet_queue_.pop();
        lock.unlock();

        // If the packet has a new timestamp, call onNewTime()
        if (currentTime_.tv_sec != packet->time.tv_sec) {
            onNewTime(packet->time);
        }

        // Add packet to the packets_and_tasks_map_
        addPacket(std::move(packet));
    }
}


void TaskManager::addPacket(std::unique_ptr<Packet> packet) {
    std::lock_guard<std::mutex> lock(packet_queue_mutex_);
    // Log that a packet is being added
    LOG(INFO) << "Adding packet " << packet->time.tv_sec << " seconds";
    packets_and_tasks_map_[packet->time.tv_sec].first.emplace_back(
        std::move(packet));

    packet_queue_cv_.notify_one();
}

void TaskManager::onNewTime(struct timeval aCurrentTime) {
    std::lock_guard<std::mutex> lock(mutex_);
    currentTime_ = aCurrentTime;
    LOG(TRACE) << "New time: " << currentTime_.tv_sec << " seconds";
}

void TaskManager::addTask(std::unique_ptr<PeriodicTask> task) {
    std::lock_guard<std::mutex> lock(mutex_);

    auto interval = task->getInterval();

    // Log that a task is being added
    LOG(INFO) << "Adding task " << task->getId() << " with interval "
              << interval << " seconds";

    packets_and_tasks_map_[interval].second.emplace_back(std::move(task));
}

void TaskManager::removeTask(PeriodicTask task) {
    std::lock_guard<std::mutex> lock(mutex_);

    // Log that a task is being removed
    LOG(INFO) << "Removing task " << task.getId() << " with interval "
              << task.getInterval() << " seconds";

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

void TaskManager::setPeriodicTaskInterval(PeriodicTask& task,
                                          int interval_sec) {
    std::lock_guard<std::mutex> lock(mutex_);

    // Log that a task is being updated
    LOG(INFO) << "Updating task " << task.getId() << " with interval "
              << interval_sec << " seconds";

    // Update the task interval
    task.setInterval(interval_sec);
}

void TaskManager::startAllTasks() {
    // Log that the task manager is starting
    LOG(INFO) << "Starting task manager";

    task_thread_ = std::thread(&TaskManager::taskThreadFunc, this);
    packet_thread_ = std::thread(&TaskManager::processPackets, this);
}

void TaskManager::stopAllTasks() {
    // Log that the task manager is stopping
    std::lock_guard<std::mutex> lock(packet_queue_mutex_);
    LOG(INFO) << "Stopping task manager";
    stop_ = true;
    packet_queue_cv_.notify_one();
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
                            // Log that the task manager is executing tasks
        LOG(INFO) << "Executing tasks";
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
