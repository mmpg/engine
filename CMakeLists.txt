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
        src
)

# Common source files
set(SOURCE_FILES
        src/utils.cpp
        src/debug.cpp
        src/log.cpp
        src/world.cpp
        src/action.cpp
        src/action/move.cpp
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

# Workers
add_executable(worker
        src/cmd/worker/main.cpp
        src/cmd/worker/player.cpp
        ${SOURCE_FILES}
)

target_link_libraries(worker
        ${ZEROMQ_LIBRARIES}
        uuid
)

# Players
add_executable(player
        src/cmd/player/main.cpp
        src/cmd/player/ai.cpp
        match/build/ai.cpp
        ${SOURCE_FILES}
)

target_link_libraries(player
        ${ZEROMQ_LIBRARIES}
        uuid
)
