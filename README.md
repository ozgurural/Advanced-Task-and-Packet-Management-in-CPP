# forescout

- main.cpp: This file contains the entry point of the program and is responsible for creating a `TaskManager` object and using it to run the periodic tasks. It should also contain a `processPackets` function that processes incoming packets and calls the `onNewTime` function when the second part of the packet's timestamp has changed.
- PeriodicTask.h: This file declares the `PeriodicTask` class, which represents a single periodic task. It should have member variables for the task's name, period, and callback function, as well as methods for starting, stopping, and updating the task.
- PeriodicTask.cpp: This file defines the implementation of the `PeriodicTask` class. It should also define the `onNewTime` function, which is called by the `processPackets` function whenever the second part of the packet's timestamp changes. The `onNewTime` function should update the `PeriodicTask` objects and call their callback functions if their period has elapsed.
- TaskManager.h: This file declares the `TaskManager` class, which is responsible for managing a set of `PeriodicTask` objects. It should have methods for adding and removing tasks, as well as for starting and stopping all tasks.
- TaskManager.cpp: This file defines the implementation of the `TaskManager` class.
