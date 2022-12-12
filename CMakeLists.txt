cmake_minimum_required(VERSION 3.13)

project(zpr_sync)
message("zpr_sync")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)

find_package(libssh REQUIRED)

message("Looking for Boost")
find_package(Boost 1.56 REQUIRED COMPONENTS unit_test_framework)

set(EXECUTABLE_NAME "zpr_sync")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
file(GLOB MAIN_SRC src/zpr_sync/*.cc include/zpr_sync/*.h)
include_directories(${PROJECT_SOURCE_DIR}/include)


link_libraries(ssh)
add_executable(zpr_sync ${MAIN_SRC} src/main.cc)

set (BUILD_DOCS True) #set TRUE if you want to build docs

set (BUILD_TESTS True) #Set to TRUE if you want to build tests

if(BUILD_TESTS)
    find_package(Test REQUIRED)

endif()

if(BUILD_DOCS)
    find_package(Doxy REQUIRED)
endif()