cmake_minimum_required(VERSION 3.13)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(PROJECT_NAME "LightAlarm")
project(${PROJECT_NAME} CXX C ASM)

enable_language(CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_C_STANDARD_REQUIRED TRUE)


if(EXISTS "${CMAKE_SOURCE_DIR}/pico-sdk")
    message("PICO SDK Found!")
else()
    message("PICO SDK Not Found, fetching...")
    execute_process(COMMAND git "clone" "https://github.com/raspberrypi/pico-sdk.git" "--branch" "master" "${CMAKE_SOURCE_DIR}/pico-sdk")
    message("Updating pico sdk...")
    execute_process(COMMAND git "submodule" "update" "--init" WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/pico-sdk")
endif()

set(ENV{PICO_SDK_PATH} "${CMAKE_SOURCE_DIR}/pico-sdk")

if(EXISTS "${CMAKE_SOURCE_DIR}/pico_sdk_import.cmake")
    message("PICO SDK CMake toolchain file found!")
else()
    message("PICO SDK CMake toolchain Not Found, fetching...")
    execute_process(COMMAND cp "${CMAKE_SOURCE_DIR}/pico-sdk/external/pico_sdk_import.cmake" "${CMAKE_SOURCE_DIR}")
endif()

include(pico_sdk_import.cmake)
pico_sdk_init()
set(SOURCES "src/main.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})
pico_add_extra_outputs(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/src/include")
target_link_libraries(${PROJECT_NAME} pico_stdlib)
