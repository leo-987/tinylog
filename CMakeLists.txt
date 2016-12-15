cmake_minimum_required(VERSION 3.6)
project(tinylog)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp TinyLog.cpp TinyLog.h LogStream.cpp LogStream.h Buffer.cpp Buffer.h Utils.cpp Utils.h Config.h)
add_executable(tinylog ${SOURCE_FILES})