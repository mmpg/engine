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
        src/world.cpp
        src/utils.cpp
        src/debug.cpp
)

# Master
add_executable(master
        src/cmd/master/main.cpp
        src/cmd/master/server.cpp
        src/cmd/master/worker.cpp
        src/cmd/master/player.cpp
        src/cmd/master/notifier.cpp
        src/cmd/master/api.cpp
        ${SOURCE_FILES}
)

target_link_libraries(master
        ${ZEROMQ_LIBRARIES}
        uuid
)

# Players
add_executable(player
        src/cmd/player/main.cpp
        match/build/ai.cpp
        ${SOURCE_FILES}
)

target_link_libraries(player
        ${ZEROMQ_LIBRARIES}
        uuid
)
