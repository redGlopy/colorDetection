cmake_minimum_required(VERSION 3.10)
project(colorDetection)

# 1. Look for OpenCV (MSYS2 stores it in the standard path)
find_package(OpenCV REQUIRED)

# 2. Tell CMake which source file to use
add_executable(colorDetection main.cpp)

# 3. Link the OpenCV libraries to your app
target_link_libraries(colorDetection ${OpenCV_LIBS})

include_directories(${OpenCV_INCLUDE_DIRS})
