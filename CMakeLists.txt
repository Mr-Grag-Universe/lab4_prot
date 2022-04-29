cmake_minimum_required(VERSION 3.16)
project(lab4_prot C)

set(CMAKE_C_STANDARD 99)

include_directories(src/binary_tree src/libs src/libs/headers src/tree_dialog Google_tests Google_tests/googletest-main)

# find_library(Lib src/binary_tree ${CMAKE_SOURCE_DIR})

# include(libs/CMakeLists.txt)
# add_subdirectory(src/libs)
# add_subdirectory(src/binary_tree)

add_subdirectory(src)
#  add_subdirectory(Google_tests)

#add_executable(lab4_prot
#        src/main.c
#        src/tree_dialog/tree_dialog.h
#        src/tree_dialog/dialog_functions.c
#        src/binary_tree/binary_tree.h
#        )
