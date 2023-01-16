message("GTest build started.")

enable_testing()
find_package(GTest REQUIRED)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/zpr_sync/*.cc)
file(GLOB TEST_SOURCES ${PROJECT_SOURCE_DIR}/test/test-*.cc)
add_executable(runUnitTests ${TEST_SOURCES} ${SOURCE_FILES})
#add_executable(runUnitTests ${PROJECT_SOURCE_DIR}/test/test-connection.cc ${SOURCE_FILES})

target_link_libraries(runUnitTests GTest::gtest GTest::gtest_main)
add_test( runUnitTests runUnitTests )
