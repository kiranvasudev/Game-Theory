cmake_minimum_required(VERSION 2.8)

project( Assignment11 )

set(CMAKE_BUILD_TYPE Debug)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

include_directories (
    include
)

add_executable( assignment11
		src/agent.cpp
        	src/env.cpp
        	src/main.cpp)


