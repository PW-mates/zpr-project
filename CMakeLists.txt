cmake_minimum_required(VERSION 3.13)
project(zpr-sync)
message("zpr-sync")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)

find_package(SSH REQUIRED)
#find_package(Boost 1.56 REQUIRED COMPONENTS program_options unit_test_framework)

add_executable(zpr-sync ${MAIN_SRC} src/main.cc)

