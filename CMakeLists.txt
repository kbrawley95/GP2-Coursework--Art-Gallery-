cmake_minimum_required (VERSION 2.8)
PROJECT (GP2-Coursework--Art-Gallery-)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
LIST(APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -ftest-coverage -fprofile-arcs")

SET(CMAKE_PREFIX_PATH "C:/Users/Kieran/Documents/Uni Work/Games Programming/OpenGLFramework/glew-1.12.0-win32/glew-1.12.0/include")
SET(CMAKE_LIBRARY_PATH "C:/Users/Kieran/Documents/Uni Work/Games Programming/OpenGLFramework/glew-1.12.0-win32/glew-1.12.0/lib/Release/x64")

FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(SDL2 REQUIRED)
FIND_PACKAGE(SDL2_Image REQUIRED)
FIND_PACKAGE(SDL2_TTF REQUIRED)
FIND_PACKAGE(GLEW REQUIRED)
FIND_PACKAGE(GLM REQUIRED)
FIND_PACKAGE(FBX REQUIRED)

FILE(GLOB C_SRCS src/*.cpp include/*.h Core/src/*.cpp Core/include/*.h)
ADD_EXECUTABLE(GP2-Coursework--Art-Gallery- ${C_SRCS})

ADD_SUBDIRECTORY(Core)

INCLUDE_DIRECTORIES(GP2-Coursework--Art-Gallery- include/ Core/include/ ${OPENGL_INCLUDE_DIRS} ${SDL2_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${FBX_INCLUDE_DIR})
# create the program
TARGET_LINK_LIBRARIES(GP2-Coursework--Art-Gallery- ${SDL2_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${SDL2IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${FBX_LIBRARY})

if (MSVC)
add_custom_command(TARGET GP2-Coursework--Art-Gallery-  POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/dlls $<TARGET_FILE_DIR:GP2-Coursework--Art-Gallery->)
endif (MSVC)

add_custom_command(TARGET GP2-Coursework--Art-Gallery-  PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                 ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:GP2-Coursework--Art-Gallery->/assets)
