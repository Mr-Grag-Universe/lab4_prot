cmake_minimum_required(VERSION 3.16)
project(lab4_prot C)

set(CMAKE_C_STANDARD 99)

include_directories(binary_tree libs libs/headers)

add_executable(lab4_prot main.c binary_tree/binary_tree.h libs/KGetLine.c libs/MyString.c binary_tree/Tree.c binary_tree/Node.c binary_tree/key_and_info.c)
