cmake_minimum_required(VERSION 3.22)

# Set the project name and language
project(forescout)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)

# Set the include directories for the forescout executable
include_directories(
    include
)

# Set the source files for the forescout executable
set(SOURCES
    src/main.cpp
    src/PeriodicTask.cpp
    src/TaskManager.cpp
    src/PeriodicTaskFactory.cpp
    src/Logger.cpp
)

# Set the header files for the forescout executable
set(HEADERS
    include/PeriodicTask.h
    include/TaskManager.h
    include/PeriodicTaskFactory.h
    include/Logger.h
    include/Packet.h
)

# Add the forescout executable with the specified source and header files
add_executable(forescout ${SOURCES} ${HEADERS})


# Link the GTest.Test library for testing
find_package(GTest REQUIRED)

# Set the source files for the test_TaskManager test
set(TEST_SOURCES
    test/test_TaskManager.cpp
)

# Add the test_TaskManager executable with the specified source files
add_executable(test_TaskManager ${TEST_SOURCES} ${SOURCES} ${HEADERS})

# Link the Google Test library to the test_TaskManager target
target_link_libraries(test_TaskManager ${GTEST_BOTH_LIBRARIES})

