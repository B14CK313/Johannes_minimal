cmake_minimum_required(VERSION 3.16)
project(Template)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/debug)
else ()
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/release)
endif ()

set(TEMPLATE_SOURCE_FILES src/main.cpp)
#set(TEMPLATE_SOURCE_FILES src/main_optional.cpp)
set(COMPILE_FLAGS "${COMPILE_FLAGS}")

include_directories()

add_definitions(${COMPILE_FLAGS})
add_executable(TEMPLATE ${TEMPLATE_SOURCE_FILES})
