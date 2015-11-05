cmake_minimum_required(VERSION 2.8)
project(engine)

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# 3rd party libraries
list(APPEND CMAKE_MODULE_PATH "${SOURCE_DIR}")
find_package(ZeroMQ REQUIRED)

include_directories(
        ${ZEROMQ_INCLUDE_DIRS}
        lib/cppzmq
)

# Common source files
set(SOURCE_FILES
        src/utils.cpp
        src/debug.cpp
)

# Master
add_executable(master
        src/master.cpp
        src/notifier.cpp
        src/server.cpp
        ${SOURCE_FILES}
)

target_link_libraries(master
        ${ZEROMQ_LIBRARIES}
)

# Players
add_executable(player
        src/player.cpp
        match/build/ai.cpp
        ${SOURCE_FILES}
)
