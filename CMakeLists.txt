cmake_minimum_required(VERSION 3.28)
project(vlknd VERSION 0.1.0)

set(PROJECT_DISPLAYNAME "DoomALike")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TARGET_NAME vlknd_client)

if(WIN32)
        set(PROJECT_ROOT_RELATIVE_PATH "../") # Path to binary dir relative to binary (it could be better but it works)
else()
        set(PROJECT_ROOT_RELATIVE_PATH "./")
endif()

# set include directories
set(SrcDIR ${CMAKE_SOURCE_DIR}/src)
set(IncludeDIR ${CMAKE_SOURCE_DIR}/include)
set(CMakeDIR ${CMAKE_SOURCE_DIR}/cmake)

include("${CMakeDIR}/deployment.cmake")
include("${CMakeDIR}/dependencies.cmake")

configure_file(${SrcDIR}/config.h.in config.h)

include_directories(
        ${SrcDIR}
        ${IncludeDIR}
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

# SOURCE
add_subdirectory(src)