cmake_minimum_required(VERSION 3.13)

project(zpr-sync)
message("zpr-sync")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)

find_package(SSH REQUIRED)
message("Looking for Boost")
find_package(Boost 1.56 REQUIRED COMPONENTS unit_test_framework)

link_libraries(ssh)
add_executable(zpr-sync ${MAIN_SRC} src/main.cc)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lssh")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lssh")




