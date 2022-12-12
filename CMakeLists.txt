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
)

# Set the header files for the forescout executable
set(HEADERS
    include/PeriodicTask.h
    include/TaskManager.h
    include/PeriodicTaskFactory.h
)

# Add the forescout executable with the specified source and header files
add_executable(forescout ${SOURCES} ${HEADERS})

# Link the Boost.Test library for testing
# find_package(Boost REQUIRED COMPONENTS test)
# target_link_libraries(periodic_task INTERFACE Boost::test)