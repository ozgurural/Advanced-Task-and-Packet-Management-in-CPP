cmake_minimum_required(VERSION 3.22)

# Set the project name and language
project(forescout)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)

add_executable(forescout main.cpp PeriodicTask.h PeriodicTask.cpp TaskManager.h TaskManager.cpp TaskFactory.cpp TaskFactory.h)

# Link the Boost.Test library for testing
# find_package(Boost REQUIRED COMPONENTS test)
# target_link_libraries(periodic_task INTERFACE Boost::test)