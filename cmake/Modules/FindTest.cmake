message("GTest build started.")

enable_testing()
find_package(GTest REQUIRED)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable( runUnitTests ${PROJECT_SOURCE_DIR}/test/test-test.cc )

target_link_libraries(runUnitTests GTest::gtest GTest::gtest_main)
add_test( runUnitTests runUnitTests )
