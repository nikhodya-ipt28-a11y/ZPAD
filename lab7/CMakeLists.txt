cmake_minimum_required(VERSION 3.10)
project(LAB7_AI)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} include)

# Збираємо всі .cpp файли в src
file(GLOB SOURCES "src/*.cpp")

add_executable(lab7_app ${SOURCES})

# Лінк з OpenCV та потоками
target_link_libraries(lab7_app ${OpenCV_LIBS} Threads::Threads)