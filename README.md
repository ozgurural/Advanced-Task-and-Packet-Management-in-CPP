# Advanced Task and Packet Management in C++

The application uses a TaskManager class to manage the execution of periodic tasks and the processing of incoming packets. The TaskManager class uses a std::map to store tasks and packets, with the key being the interval of the tasks. The TaskManager class also has a std::jthread that executes the tasks and processes the packets at their respective intervals.

### Requirements
- A C++ compiler that supports C++20 or later
- CMake 3.22 or later
- Google Test (optional, for unit tests)

### Directory Structure
The project consists of the following directories:

- include - This directory contains the header files for the project.
- src - This directory contains the source files for the project.
- test - This directory contains the unit tests for the project.

### Components
The project consists of the following components:

- PeriodicTask: A class representing a periodic task that can be executed at regular intervals. It takes an interval and a lambda function as arguments in its constructor and has a method called execute that executes the lambda function. It also has a method called isTimeToExecute that returns true if the interval has passed since the last time the task was executed.

- TaskManager: A class responsible for managing periodic tasks and packets. It has a map of intervals and associated tasks and packets, a queue of incoming packets, and a thread that executes periodic tasks at their respective intervals. It has methods to add and remove tasks, set the interval of a task, add packets to the queue, start and stop all tasks, and process packets. It also has a static method called getTimeSource that returns the current time.

- Packet: A class representing a packet with a timestamp and data.

- PeriodicTaskFactory: A class with a static method called createPeriodicTask that takes an interval and a lambda function as arguments and returns a shared pointer to a PeriodicTask object.

- Logger: A class with static methods for logging messages at different levels (e.g., info, warning, error).

- main.cpp: This is the main function for a program that uses the TaskManager class defined in the previous code snippet. The function creates an object of type TaskManager and calls the startAllTasks() method to start the threads that process incoming packets and execute the periodic tasks. Then, it waits for the user to press Enter before calling the stopAllTasks() method to stop these threads and terminate the program.



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
A sample output of forescout executable is as the following:
```sh
ozgurural@ozgurural:~/Desktop/forescout/forescout-cpp-challange/build$ ./forescout 
[INFO][2022-12-18 18:49:57.890151]: Adding packet 5000 seconds
[INFO][2022-12-18 18:49:57.890218]: Number of packets added: 1
[INFO][2022-12-18 18:49:57.890230]: Adding packet 5000 seconds
[INFO][2022-12-18 18:49:57.890239]: Number of packets added: 2
[INFO][2022-12-18 18:49:57.890250]: Adding task 0 with interval 5000 seconds
[INFO][2022-12-18 18:49:57.890259]: Number of packets before adding task: 2
[INFO][2022-12-18 18:49:57.890267]: Number of packets after adding task: 2
[INFO][2022-12-18 18:49:57.890275]: Adding task 1 with interval 5000 seconds
[INFO][2022-12-18 18:49:57.890282]: Number of packets before adding task: 2
[INFO][2022-12-18 18:49:57.890290]: Number of packets after adding task: 2
[INFO][2022-12-18 18:49:57.890298]: Adding task 2 with interval 1000 seconds
[INFO][2022-12-18 18:49:57.890306]: Number of packets before adding task: 0
[INFO][2022-12-18 18:49:57.890314]: Number of packets after adding task: 0
[TRACE][2022-12-18 18:49:57.890322]: New time: 5000 seconds
[INFO][2022-12-18 18:49:57.890329]: Starting task manager
[INFO][2022-12-18 18:49:57.890418]: Process Packets thread running
[INFO][2022-12-18 18:49:57.890435]: Task thread running
[INFO][2022-12-18 18:49:58.390675]: Process Packets thread running
[INFO][2022-12-18 18:49:58.890606]: Task thread running
[INFO][2022-12-18 18:49:58.890860]: Process Packets thread running
[INFO][2022-12-18 18:49:59.391319]: Process Packets thread running
[INFO][2022-12-18 18:49:59.890822]: Task thread running
[INFO][2022-12-18 18:49:59.891474]: Process Packets thread running
[INFO][2022-12-18 18:50:00.391885]: Process Packets thread running
[INFO][2022-12-18 18:50:00.891051]: Task thread running
[INFO][2022-12-18 18:50:00.892122]: Process Packets thread running
[INFO][2022-12-18 18:50:01.392367]: Process Packets thread running
[INFO][2022-12-18 18:50:01.891300]: Task thread running
[INFO][2022-12-18 18:50:01.892574]: Process Packets thread running
[INFO][2022-12-18 18:50:02.392828]: Process Packets thread running
[INFO][2022-12-18 18:50:02.891555]: Task thread running
[INFO][2022-12-18 18:50:02.891654]: Executing tasks
FUNC-1- Packet data: 1 2 3 4 
[INFO][2022-12-18 18:50:02.891698]: Executing tasks
FUNC-1- Packet data: 15 16 17 18 
[INFO][2022-12-18 18:50:02.891730]: Executing tasks
FUNC-2- Packet data: 1 2 3 4 
[INFO][2022-12-18 18:50:02.891758]: Executing tasks
FUNC-2- Packet data: 15 16 17 18 
[INFO][2022-12-18 18:50:02.893065]: Process Packets thread running
[INFO][2022-12-18 18:50:03.393330]: Process Packets thread running
[INFO][2022-12-18 18:50:03.891892]: Task thread running
[INFO][2022-12-18 18:50:03.893534]: Process Packets thread running
[INFO][2022-12-18 18:50:04.393781]: Process Packets thread running

[INFO][2022-12-18 18:50:04.889617]: Stop all tasks will be called from main
[INFO][2022-12-18 18:50:04.889726]: Stopping task thread
[INFO][2022-12-18 18:50:04.892245]: Task thread stopped
[INFO][2022-12-18 18:50:04.892311]: Stopping packet thread
[INFO][2022-12-18 18:50:04.894096]: Packet thread stopped

[INFO][2022-12-18 18:50:08.938904]: Stopping task thread
[WARNING][2022-12-18 18:50:08.938961]: Task thread is not joinable
[INFO][2022-12-18 18:50:08.938986]: Stopping packet thread
[WARNING][2022-12-18 18:50:08.939009]: Packet thread is not joinable
```

To run the unit tests, execute the following command: 
```sh
./unit_tests
```
A sample output of unit_tests is as the following:
```sh
ozgurural@ozgurural:~/Desktop/forescout/forescout-cpp-challange/build$ ./unit_tests 
Running main() from /home/ozgurural/Downloads/googletest/googletest/src/gtest_main.cc
[==========] Running 12 tests from 4 test suites.
[----------] Global test environment set-up.
[----------] 5 tests from TaskManagerTest
[ RUN      ] TaskManagerTest.addPacket
[INFO][2022-12-18 18:53:22.784566]: Adding packet 5000 seconds
[INFO][2022-12-18 18:53:22.784623]: Number of packets added: 1
[INFO][2022-12-18 18:53:22.784643]: Stopping task thread
[WARNING][2022-12-18 18:53:22.784654]: Task thread is not joinable
[INFO][2022-12-18 18:53:22.784665]: Stopping packet thread
[WARNING][2022-12-18 18:53:22.784676]: Packet thread is not joinable
[       OK ] TaskManagerTest.addPacket (0 ms)
[ RUN      ] TaskManagerTest.addTask
[INFO][2022-12-18 18:53:22.784712]: Adding task 0 with interval 5000 seconds
[INFO][2022-12-18 18:53:22.784726]: Number of packets before adding task: 0
[INFO][2022-12-18 18:53:22.784739]: Number of packets after adding task: 0
[INFO][2022-12-18 18:53:22.784752]: Stopping task thread
[WARNING][2022-12-18 18:53:22.784763]: Task thread is not joinable
[INFO][2022-12-18 18:53:22.784773]: Stopping packet thread
[WARNING][2022-12-18 18:53:22.784783]: Packet thread is not joinable
[       OK ] TaskManagerTest.addTask (0 ms)
[ RUN      ] TaskManagerTest.TestAddTask
[INFO][2022-12-18 18:53:22.784814]: Adding task 1 with interval 1 seconds
[INFO][2022-12-18 18:53:22.784827]: Number of packets before adding task: 0
[INFO][2022-12-18 18:53:22.784838]: Number of packets after adding task: 0
[INFO][2022-12-18 18:53:22.784849]: Stopping task thread
[WARNING][2022-12-18 18:53:22.784859]: Task thread is not joinable
[INFO][2022-12-18 18:53:22.784869]: Stopping packet thread
[WARNING][2022-12-18 18:53:22.784879]: Packet thread is not joinable
[       OK ] TaskManagerTest.TestAddTask (0 ms)
[ RUN      ] TaskManagerTest.TestAddAndRemoveTask
[INFO][2022-12-18 18:53:22.784909]: Adding task 2 with interval 1 seconds
[INFO][2022-12-18 18:53:22.784922]: Number of packets before adding task: 0
[INFO][2022-12-18 18:53:22.784934]: Number of packets after adding task: 0
[INFO][2022-12-18 18:53:22.784945]: Removing task 2 with interval 1 seconds
[INFO][2022-12-18 18:53:22.784958]: Stopping task thread
[WARNING][2022-12-18 18:53:22.784968]: Task thread is not joinable
[INFO][2022-12-18 18:53:22.784978]: Stopping packet thread
[WARNING][2022-12-18 18:53:22.784988]: Packet thread is not joinable
[       OK ] TaskManagerTest.TestAddAndRemoveTask (0 ms)
[ RUN      ] TaskManagerTest.TestChangeTaskInterval
[INFO][2022-12-18 18:53:22.785016]: Adding task 3 with interval 1 seconds
[INFO][2022-12-18 18:53:22.785029]: Number of packets before adding task: 0
[INFO][2022-12-18 18:53:22.785041]: Number of packets after adding task: 0
[INFO][2022-12-18 18:53:22.785052]: Changing interval of task 3 from 1 seconds to 2 seconds
[INFO][2022-12-18 18:53:22.785067]: Stopping task thread
[WARNING][2022-12-18 18:53:22.785076]: Task thread is not joinable
[INFO][2022-12-18 18:53:22.785087]: Stopping packet thread
[WARNING][2022-12-18 18:53:22.785097]: Packet thread is not joinable
[       OK ] TaskManagerTest.TestChangeTaskInterval (0 ms)
[----------] 5 tests from TaskManagerTest (0 ms total)

[----------] 4 tests from PeriodicTaskTest
[ RUN      ] PeriodicTaskTest.Constructor
[       OK ] PeriodicTaskTest.Constructor (0 ms)
[ RUN      ] PeriodicTaskTest.SetInterval
[       OK ] PeriodicTaskTest.SetInterval (0 ms)
[ RUN      ] PeriodicTaskTest.Execute
[       OK ] PeriodicTaskTest.Execute (0 ms)
[ RUN      ] PeriodicTaskTest.IsTimeToExecute
[       OK ] PeriodicTaskTest.IsTimeToExecute (1100 ms)
[----------] 4 tests from PeriodicTaskTest (1100 ms total)

[----------] 1 test from PeriodicTaskFactoryTest
[ RUN      ] PeriodicTaskFactoryTest.CreatePeriodicTask
[       OK ] PeriodicTaskFactoryTest.CreatePeriodicTask (0 ms)
[----------] 1 test from PeriodicTaskFactoryTest (0 ms total)

[----------] 2 tests from Logger
[ RUN      ] Logger.LogLevelToString
[       OK ] Logger.LogLevelToString (0 ms)
[ RUN      ] Logger.GetCurrentTimeAsString
[       OK ] Logger.GetCurrentTimeAsString (5 ms)
[----------] 2 tests from Logger (5 ms total)

[----------] Global test environment tear-down
[==========] 12 tests from 4 test suites ran. (1106 ms total)
[  PASSED  ] 12 tests.
```
