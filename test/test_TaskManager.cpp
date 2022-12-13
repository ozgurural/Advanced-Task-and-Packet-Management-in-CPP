#include "TaskManager.h"
#include "PeriodicTaskFactory.h"
#include "gtest/gtest.h"

TEST(TaskManagerTest, AddTask) {
    // Create a new TaskManager instance
    auto& task_manager = TaskManager::getInstance();

    // Create a new task using the PeriodicTaskFactory
    auto& task_factory = PeriodicTaskFactory::getInstance();
    std::unique_ptr<PeriodicTask> task = task_factory.createPeriodicTask(1, []() {
        // Your code here
    });

    // Add the task to the TaskManager
    task_manager.addTask();

    // Check if the task was added to the TaskManager's list of tasks
    auto tasks = task_manager.getTasks();
    auto interval = task->getInterval();
    auto it = tasks.find(interval);
    ASSERT_TRUE(it != tasks.end());

    auto& task_vec = it->second;
    auto found = std::find_if(task_vec.begin(), task_vec.end(), 
        [&task](const std::unique_ptr<PeriodicTask>& t) {
            return t->getId() == task->getId();
        });
    ASSERT_TRUE(found != task_vec.end());
}
