project(binary_tree)

add_library(binary_tree STATIC
        file_input.c
        iterator.c
        key_and_info.c
        Node.c
        Tree.c
        graphviz_modul.c)