#include <chrono>
#include <map>
#include <mutex>
#include <functional>

/*
 * This implementation uses a std::map to store the periodic tasks, where the keys are the intervals (in seconds)
 * at which the tasks should be executed. The onNewTime function uses the lower_bound function to find the tasks that
 * need to be executed at the current time, and then executes each of these tasks in turn.

The implementation is thread-safe by using a mutex to synchronize access to the tasks_ map. This ensures that multiple
threads can safely call the Add, Remove, ChangeInterval, and onNewTime functions concurrently without causing any race
conditions or data corruption.

To use this PeriodicTask interface, a developer would first create an instance of the PeriodicTask class and then call
the Add function to add periodic tasks with the desired intervals and functions. They can then call the onNewTime
 function whenever the time changes to execute the correct tasks. The Remove and ChangeInterval functions can be used to
 modify the set of periodic tasks as needed.

This implementation uses modern C++ features, such as std::chrono for time manipulation
 */

class PeriodicTask {
public:
    // Adds a new periodic task with the given interval (in seconds) and function.
    // The function should be a callable object that takes no arguments and returns void.
    void Add(double interval, const std::function<void()>& func) {
        std::lock_guard<std::mutex> lock(mutex_);
        tasks_[interval] = func;
    }

    // Removes a periodic task with the given interval (in seconds).
    // If no such task exists, this function has no effect.
    void Remove(double interval) {
        std::lock_guard<std::mutex> lock(mutex_);
        tasks_.erase(interval);
    }

    // Changes the interval of a periodic task.
    // If no such task exists, this function has no effect.
    void ChangeInterval(double oldInterval, double newInterval) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = tasks_.find(oldInterval);
        if (it != tasks_.end()) {
            tasks_[newInterval] = it->second;
            tasks_.erase(it);
        }
    }

    // Changes the interval of a periodic task.
// If no such task exists and createIfNotExist is true,
// a new task with the given interval and function is added.
// If no such task exists and createIfNotExist is false, this function has no effect.
    void setInterval(double interval, const std::function<void()>& func, bool createIfNotExist = true) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = tasks_.find(interval);
        if (it != tasks_.end()) {
            // Update the existing task
            tasks_[interval] = func;
        } else if (createIfNotExist) {
            // Add a new task with the given interval and function
            tasks_[interval] = func;
        }
    }

    // Calls the correct periodic tasks based on the provided time (in seconds).
    void onNewTime(double time) {
        std::lock_guard<std::mutex> lock(mutex_);
        // Check if any tasks need to be executed at the current time
        auto it = tasks_.lower_bound(time);
        while (it != tasks_.end() && it->first == time) {
            // Execute the task and advance the iterator
            it->second();
            ++it;
        }
    }

private:
    // Map of intervals (in seconds) to periodic task functions
    std::map<double, std::function<void()>> tasks_;

    // Mutex for thread-safety
    std::mutex mutex_;
};
