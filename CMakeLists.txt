cmake_minimum_required(VERSION 3.10)
project(colorDetection)

# OpenCV
find_package(OpenCV REQUIRED)

# Your headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/hpp)

# OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(colorDetection
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/cursorMovment.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cpp/objectDetection.cpp
    ${GRT_SOURCES}   # compiles all GRT .cpp files
)

target_link_libraries(colorDetection ${OpenCV_LIBS})
