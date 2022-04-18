//
// Created by Stephan on 17.04.2022.
//
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "Errors.h"
#include "binary_tree.h"

Tree * init_tree() {
    Tree * tree = malloc(sizeof(Tree));
    if (tree == NULL) {
        fprintf(stderr, "Cannot alloc memory for tree!\n");
        exit(MEMORY_OVERFLOW);
    }

    tree->root = NULL;
    return tree;
}

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

    while (node) {
        if (!key_cmp(key, node->key)) {
            fprintf(stderr, "There is element with such key in this tree.\n");
            return WRONG_INPUT;
        }
        if (key_cmp(key, node->key) > 0) {
            if (node->right == NULL) {
                break;
            }
            node = node->right;
        } else {
            if (node->left == NULL) {
                break;
            }
            node = node->left;
        }
    }

    // node = get_node_from_BT(tree, key);
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

/// deletes element from binary tree with key, return IT_IS_OK if deleting was successful
Error delete_el_from_BT(Tree * tree, KeyType * key) {
    Node * node = get_node_from_BT(tree, key);
    if (node == NULL) {
        return NOT_FOUND;
    }

    // max element in the left child-tree
    Node * max_node = get_max_node(node->left);
    // min element in the right child-tree
    Node * min_node = get_min_node(node->right);

    /*
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

    } else {
        //TODO
    }
     */

    if (min_node) {
        if (node->previous) {
            if (node->previous->left == node) {
                node->previous->left = min_node;
            } else {
                node->previous->right = min_node;
            }
            min_node->previous->left = min_node->right;
        } else {
            tree->root = min_node;
            min_node->previous = NULL;
        }

        if (node->right) {
            node->right->previous = min_node;
        }
        if (node->left) {
            node->left->previous = min_node;
        }

        if (min_node != node->right)
            min_node->right = node->right;
        else
            min_node->right = NULL;

        min_node->left = node->left;
        min_node->previous = node->previous;
    }
    else if (max_node) {
        if (node->previous) {
            if (node->previous->left == node) {
                node->previous->left = max_node;
            } else {
                node->previous->right = max_node;
            }
            max_node->previous->right = max_node->left;
        } else {
            tree->root = max_node;
            max_node->previous = NULL;
        }

        if (node->left) {
            node->left->previous = max_node;
        }
        if (node->right) {
            node->right->previous = max_node;
        }

        max_node->right = node->right;

        if (max_node != node->left)
            max_node->left = node->left;
        else
            max_node->left = NULL;

        max_node->previous = node->previous;
    }
    else {
        if (node->previous) {
            if (node->previous->left == node) {
                node->previous->left = NULL;
            } else {
                node->previous->right = NULL;
            }
        } else {
            tree->root = NULL;
        }
    }

    free_node(node);

    return IT_IS_OK;
}

// TBT
InfoType * get_info_from_BT(const Tree * tree, KeyType * key) {
    Node * node = get_node_from_BT(tree, key);
    if (node == NULL) {
        fprintf(stderr, "There is no element with such key in this tree.\n");
        return NULL;
    }
    return node->info;
}

Node * get_node_from_BT(const Tree * tree, KeyType * key) {
    if (tree == NULL || key == NULL) {
        fprintf(stderr, "Something in arguments is NULL.\n");
        return NULL;
    }

    Node * node = tree->root;
    while (node) {
        if (!key_cmp(key, node->key)) {
            return node;
        }
        if (key_cmp(key, node->key) > 0) {
            if (node->right == NULL) {
                fprintf(stderr, "There is no element with such key in this tree.\n");
                return NULL;
            }
            node = node->right;
        } else {
            if (node->left == NULL) {
                fprintf(stderr, "There is no element with such key in this tree.\n");
                return NULL;
            }
            node = node->left;
        }
    }

    return node;
}

Error recursion_print_BT(Node* node, int offset) {
    for (int i = 0; i < offset; ++i)
        printf(" ");
    if (node == NULL) {
        printf("null\n");
        return IT_IS_OK;
    }
    print_key(node->key);

    for (int i = 0; i < offset; ++i)
        printf(" ");
    print_info(node->info);

    recursion_print_BT(node->left, offset+1);
    recursion_print_BT(node->right, offset+1);

    return IT_IS_OK;
}

Error print_BT(const Tree * tree) {
    if (tree->root == NULL) {
        printf("This tree is empty.\n");
        return IT_IS_OK;
    }
    return recursion_print_BT(tree->root, 0);
}

Error free_BT(Tree * tree) {
    if (tree == NULL) {
        fprintf(stderr, "NULL tree pointer tried to be freed\n");
        return FREEING_OF_NULL_PTR;
    }

    if (recursion_free_BT(tree->root) != IT_IS_OK) {
        fprintf(stderr, "Something came wrong with running of recursion freeing.\n");
        return WRONG_INPUT;
    }

    free(tree);

    return IT_IS_OK;
}

InfoType ** traversal_tree(Tree* tree) {
    if (tree == NULL) {
        fprintf(stderr, "Tree pointer is NULL");
        return NULL;
    }

    TreeIteratorContainer * container = create_iterator(tree);
    if (container == NULL) {
        fprintf(stderr, "NULL pointer of container have been got after it's creation.\n");
        return NULL;
    }

    InfoType ** info_array = malloc(sizeof(InfoType*) * (container->number_of_elements+1));
    for (size_t i = 0; i < container->number_of_elements; ++i) {
        if (container->iterator == NULL) {
            fprintf(stderr, "WARNING: NULL pointer to the info here.\n");
            continue;
        }
        info_array[i] = container->iterator[i]->info;
    }

    info_array[container->number_of_elements] = NULL;

    return info_array;
}