# FINAL VERSION

include_directories(binary_tree libs libs/headers tree_dialog)

find_library(Lib binary_tree ${CMAKE_SOURCE_DIR})

# include(libs/CMakeLists.txt)
add_subdirectory(libs)
add_subdirectory(binary_tree)

add_executable(lab4_prot
        main.c
        tree_dialog/tree_dialog.h
        tree_dialog/dialog_functions.c
        binary_tree/binary_tree.h
        )

target_link_libraries(lab4_prot mylib)
target_link_libraries(binary_tree mylib)
target_link_libraries(lab4_prot binary_tree)
