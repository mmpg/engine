cmake_minimum_required(VERSION 2.8)
project(engine)

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

# 3rd party libraries
list(APPEND CMAKE_MODULE_PATH "${SOURCE_DIR}")
find_package(ZeroMQ REQUIRED)
find_package(Threads)

include_directories(
        ${ZEROMQ_INCLUDE_DIRS}
        lib/cppzmq
        include/mmpg
)

# Common source files
set(SOURCE_FILES
        src/utils.cpp
        src/base64.cpp
        src/debug.cpp
        src/log.cpp
        src/game.cpp
        src/world.cpp
        src/action.cpp
)

# Master
set(MMPG_MASTER_SOURCE_FILES
        src/master/process.cpp
        src/master/server.cpp
        src/master/worker.cpp
        src/master/player.cpp
        src/master/notifier.cpp
        src/master/api.cpp
        ${SOURCE_FILES}
)

set(MMPG_PLAYER_SOURCE_FILES
        src/player/process.cpp
        src/player/ai.cpp
        ${SOURCE_FILES}
)


add_library(MMPGMaster ${MMPG_MASTER_SOURCE_FILES})
add_library(MMPGPlayer ${MMPG_PLAYER_SOURCE_FILES})

# Shared variables
set(MMPG_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL "DIRS")
set(MMPG_LIBRARIES
        ${ZEROMQ_LIBRARIES}
        uuid
        ${CMAKE_THREAD_LIBS_INIT}

        CACHE INTERNAL "DIRS"
)
