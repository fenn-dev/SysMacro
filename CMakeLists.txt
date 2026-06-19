cmake_minimum_required(VERSION 3.15)
project(OS_Macro VERSION 1.0.0 LANGUAGES CXX)

# Define a header-only interface target for anyone including this project
add_library(os_macro INTERFACE)
target_include_directories(os_macro INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Only build the test executable if this is the root/top-level project
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(STATUS "OS_Macro: Building standalone verification tests.")
    
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    add_executable(verify_macro tests/verify.cpp)
    target_link_libraries(verify_macro PRIVATE os_macro)
endif()