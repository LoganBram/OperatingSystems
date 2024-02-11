cmake_minimum_required(VERSION 3.27)
project(Lab2)

set(CMAKE_CXX_STANDARD 14)

include_directories(schedulingalgorithms)

add_executable(Lab2
        schedulingalgorithms/CPUScheduler.cpp
        schedulingalgorithms/CPUScheduler.h
        schedulingalgorithms/FirstComeFirstServedScheduler.cpp
        schedulingalgorithms/FirstComeFirstServedScheduler.h
        schedulingalgorithms/Process.h
        schedulingalgorithms/RoundRobinScheduler.cpp
        schedulingalgorithms/RoundRobinScheduler.h
        main.cpp)
