//
// Created by Stephan on 17.04.2022.
//
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "Errors.h"
#include "binary_tree.h"

/// adds element into binary tree
/// return IT_IS_OK if adding was successful
Error add_el_into_BT(Tree * tree, KeyType * key, InfoType * info) {
    if (tree == NULL || key == NULL) {
        fprintf(stderr, "Error in add.\nSomething in arguments is NULL.\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }

    Node * node = tree->root;
    if (node == NULL) {
        tree->root = init_node();

        if (tree->root == NULL) {
            fprintf(stderr, "There is not memory enough for malloc in add function.\n");
            return MEMORY_OVERFLOW;
        }

        tree->root->info = info;
        tree->root->key = key;

        return IT_IS_OK;
    }

    node = get_node_from_BT(tree, key);
    if (node == NULL) {
        fprintf(stderr, "something in the adding search came wrong.\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }

    enum Branch {
        RIGHT,
        LEFT,
    } flag;
    flag = (key_cmp(key, node->key) > 0) ? RIGHT : LEFT;

    if ((node->right && flag == RIGHT) || (node->left && flag == LEFT)) {
        fprintf(stderr, "Not empty direction of adding.\n");
        return RUNTIME_ERROR;
    }

    if (flag == RIGHT) {
        node->right = init_node();
        node->right->previous = node;
        node->right->key = key;
        node->right->info = info;
    } else {
        node->left = init_node();
        node->left->previous = node;
        node->left->key = key;
        node->left->info = info;
    }

    return IT_IS_OK;
}

Error delete_el_from_BT(Tree * tree, KeyType * key) {
    Node * node = get_node_from_BT(tree, key);
    if (node == NULL) {
        return NOT_FOUND;
    }

    Node * max_node = get_max_node(node);
    Node * min_node = get_min_node(node);

    if (min_node == max_node) {
        if (node->previous) {
            if (node->previous->left == node) {
                node->previous->left = NULL;
            } else {
                node->previous->right = NULL;
            }
        } else {
            tree->root = NULL;
        }
        if (free_node(node) == FREEING_OF_NULL_PTR) {
            fprintf(stderr, "Invalid free in delete function.\n");
            return FREEING_OF_NULL_PTR;
        }
        return IT_IS_OK;
    }

    if (max_node != node) {
        //TODO
    } else {
        //TODO
    }

    return IT_IS_OK;
}

// TBT
InfoType * get_info_from_BT(const Tree * tree, KeyType * key) {
    return NULL;
}

Node * get_node_from_BT(const Tree * tree, KeyType * key) {
    if (tree == NULL || key == NULL) {
        fprintf(stderr, "Error in add.\nSomething in arguments is NULL.\n");
        return NULL;
    }

    Node * node = tree->root;
    while (node) {
        if (!key_cmp(key, node->key)) {
            fprintf(stderr, "There is element with such key in this tree.\n");
            return NULL;
        }
        if (key_cmp(key, node->key) > 0) {
            if (node->right == NULL)
                break;
            node = node->right;
        } else {
            if (node->left == NULL)
                break;
            node = node->left;
        }
    }

    return node;
}

Error print_BT(const Tree * tree) {
    return IT_IS_OK;
}

Error free_BT(Tree * tree) {
    return IT_IS_OK;
}