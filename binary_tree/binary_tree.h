//
// Created by Stephan on 17.04.2022.
//

#ifndef LAB4_PROT_BINARY_TREE_H
#define LAB4_PROT_BINARY_TREE_H
#include "string.h"
#include "stdio.h"
#include "stdbool.h"
#include "Errors.h"

///==============KEY=============

typedef struct KeyType {
    size_t keySize;
    char * strKey;
} KeyType;
KeyType * init_key();
int key_cmp(KeyType * key1, KeyType * key2);
/// copy src key to key                                     \n
/// free strKey in key if it's not NULL                     \n
/// return false if there is NULL and true in another case  \n
bool copy_key(KeyType * key, KeyType * src);
bool print_key(KeyType * key);
Error free_key(KeyType * key);

///===============INFO===============

typedef struct InfoType {
    unsigned int val;
} InfoType;
/// just put src.val into info.val              \n
/// if there is NULL return false, else true    \n
bool copy_info(InfoType * info, InfoType * src);
bool print_info(InfoType * info);
Error free_info(InfoType * info);

///=============NODE===============

typedef struct Node {
    KeyType * key;
    InfoType * info;
    struct Node * right;
    struct Node * left;
    struct Node * previous;
} Node;
Node * init_node();
InfoType * get_info_from_node(const Node * node);
Node * get_max_node(const Node * node);
Node * get_min_node(const Node * node);
Error print_node(const Node * node);
Error free_node(Node * node);

///=============TREE===============

typedef struct Tree {
    Node * root;
} Tree;
Error add_el_into_BT(Tree * tree, KeyType * key, InfoType * info);
Error delete_el_from_BT(Tree * tree, KeyType * key);
// TBT
InfoType * get_info_from_BT(const Tree * tree, KeyType * key);
Node * get_node_from_BT(const Tree * tree, KeyType * key);
Error print_BT(const Tree * tree);
Error free_BT(Tree * tree);

#endif //LAB4_PROT_BINARY_TREE_H
