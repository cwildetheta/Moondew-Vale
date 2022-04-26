cmake_minimum_required(VERSION 3.22.3)

project(MoondewVale VERSION 1.0.0)

include_directories(include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}")

set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

add_executable(${PROJECT_NAME} src/base_functions.cpp src/field.cpp src/crop.cpp src/orchard.cpp src/multicrop.cpp src/building.cpp src/farmhouse.cpp src/granary.cpp src/brewery.cpp src/workhouse.cpp src/functions.cpp src/main.cpp)