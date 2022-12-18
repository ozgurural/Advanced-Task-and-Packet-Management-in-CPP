cmake_minimum_required(VERSION 3.22)

# Set the project name and language
project(forescout)

# Enable testing
enable_testing()

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)

# Set the include directories for the forescout executable
include_directories(
    include
)

# Set the source files for the forescout executable
set(SOURCES
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
add_executable(forescout src/main.cpp ${SOURCES} ${HEADERS})


# Link the GTest.Test library for testing
find_package(GTest REQUIRED)

# Set the source files for the unit tests
set(TEST_SOURCES
    test/test_TaskManager.cpp
    test/test_PeriodicTask.cpp
    test/test_PeriodicTaskFactory.cpp
    test/test_Logger.cpp
)

# Add the unit tests executable with the necessary source and header files
add_executable(unit_tests ${TEST_SOURCES} ${HEADERS} ${SOURCES})

# Link the Google Test libraries to the unit tests
target_link_libraries(unit_tests ${GTEST_BOTH_LIBRARIES})

# Add the unit tests to be run by CTest
add_test(test_TaskManager unit_tests)
add_test(test_PeriodicTask unit_tests)
add_test(test_PeriodicTaskFactory unit_tests)
add_test(test_Logger unit_tests)
