cmake_minimum_required(VERSION 3.10)
project(CameraLab)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS} include)

file(GLOB SOURCES "src/*.cpp")

add_executable(lab6_app ${SOURCES})
target_link_libraries(lab6_app ${OpenCV_LIBS})