# FINAL VERSION

include_directories(binary_tree libs libs/headers tree_dialog)

# include(libs/CMakeLists.txt)
add_subdirectory(libs)
add_subdirectory(binary_tree)
add_subdirectory(tree_dialog)

add_executable(lab4_prot
        main.c
        )

target_link_libraries(lab4_prot mylib)
target_link_libraries(binary_tree mylib)
target_link_libraries(lab4_prot binary_tree)
target_link_libraries(dialog binary_tree)
target_link_libraries(dialog mylib)
target_link_libraries(lab4_prot dialog)
