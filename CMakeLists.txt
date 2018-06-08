cmake_minimum_required(VERSION 3.10)
project(factory_thread_simulation)

set(CMAKE_CXX_STANDARD 17)

add_executable(factory_thread_simulation main.cpp threads/FactoryWorker.cpp threads/FactoryWorker.h resources/Tool.cpp resources/Tool.h)