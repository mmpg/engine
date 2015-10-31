cmake_minimum_required(VERSION 2.8)
project(engine)

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# 3rd party libraries
list(APPEND CMAKE_MODULE_PATH "${SOURCE_DIR}")
find_package(ZeroMQ REQUIRED)
IF (ZEROMQ_FOUND)
        include_directories(${ZEROMQ_INCLUDE_DIRS})
        list(APPEND MORE_LIBRARIES ${ZEROMQ_LIBRARIES})
ELSE (ZEROMQ_FOUND)
        message( FATAL_ERROR "ZeroMQ not found." )
ENDIF (ZEROMQ_FOUND)

# Executables
set(SOURCE_FILES src/main.cpp)
add_executable(engine ${SOURCE_FILES})

target_link_libraries(engine
        ${ZEROMQ_LIBRARIES}
)
