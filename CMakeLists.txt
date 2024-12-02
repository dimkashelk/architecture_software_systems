cmake_minimum_required(VERSION 3.30)
project(architecture_software_systems)

set(CMAKE_CXX_STANDARD 20)

add_executable(architecture_software_systems main.cpp
        code/execution_status.h
        code/order.h
        code/order.cpp)
