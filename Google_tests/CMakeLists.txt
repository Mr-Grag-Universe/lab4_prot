project(Google_tests)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../src/binary_tree)
add_subdirectory(googletest-main)

add_executable(Google_Tests_run my_tests.cpp)
target_link_libraries(Google_Tests_run gtest gtest_main)
target_link_libraries(Google_Tests_run binary_tree)
