# Forescout - Technical challenge C++ position

The application uses a TaskManager class to manage the execution of periodic tasks and the processing of incoming packets. The TaskManager class uses a std::map to store tasks and packets, with the key being the interval of the tasks. The TaskManager class also has a std::jthread that executes the tasks and processes the packets at their respective intervals.

### Requirements
- A C++ compiler that supports C++20 or later
- CMake 3.22 or later
- Google Test (optional, for unit tests)


### Building and Running the Project
To build the project, create a build directory and run CMake in it:

```sh
mkdir build
cd build
cmake ..
```
This will generate the necessary build files. To build the project, run:

```sh
make
```

This will build the forescout executable. To run the executable, run:

```sh
./forescout
```
To run the unit tests, execute the following command: 
```sh
./unit_tests
```

### Directory Structure
The project consists of the following directories:

- include - This directory contains the header files for the project.
- src - This directory contains the source files for the project.
- test - This directory contains the unit tests for the project.

#### Components
The project consists of the following components:

- PeriodicTask: A class representing a periodic task that can be executed at regular intervals. It takes an interval and a lambda function as arguments in its constructor and has a method called execute that executes the lambda function. It also has a method called isTimeToExecute that returns true if the interval has passed since the last time the task was executed.

- TaskManager: A class responsible for managing periodic tasks and packets. It has a map of intervals and associated tasks and packets, a queue of incoming packets, and a thread that executes periodic tasks at their respective intervals. It has methods to add and remove tasks, set the interval of a task, add packets to the queue, start and stop all tasks, and process packets. It also has a static method called getTimeSource that returns the current time.

- Packet: A class representing a packet with a timestamp and data.

- PeriodicTaskFactory: A class with a static method called createPeriodicTask that takes an interval and a lambda function as arguments and returns a shared pointer to a PeriodicTask object.

- Logger: A class with static methods for logging messages at different levels (e.g., info, warning, error).

- main.cpp: This is the main function for a program that uses the TaskManager class defined in the previous code snippet. The function creates an object of type TaskManager and calls the startAllTasks() method to start the threads that process incoming packets and execute the periodic tasks. Then, it waits for the user to press Enter before calling the stopAllTasks() method to stop these threads and terminate the program.
