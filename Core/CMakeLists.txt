cmake_minimum_required (VERSION 2.8)
PROJECT (Core)

FILE(GLOB C_SRCS src/*.cpp include/*.h)
ADD_EXECUTABLE(Core ${C_SRCS})