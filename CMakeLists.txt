cmake_minimum_required(VERSION 3.9)
project(factory_thread_simulation)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread ")

add_executable(factory_thread_simulation main.cpp threads/FactoryWorker.cpp threads/FactoryWorker.h resources/Tool.cpp resources/Tool.h gui/DrawGui.cpp gui/DrawGui.h resources/Workplace.cpp resources/Workplace.h threads/Courier.cpp threads/Courier.h resources/PartsStorage.cpp resources/PartsStorage.h resources/ProductStockpille.cpp resources/ProductStockpille.h)
target_link_libraries(factory_thread_simulation curses)