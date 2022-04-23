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
    if (tree == NULL || key == NULL || key->strKey == NULL) {
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
            //fprintf(stderr, "There is element with such key in this tree.\n");
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

Error delete_list_or_one_child_node(Tree * tree, Node * node) {
    if (node == NULL) {
        return FREEING_OF_NULL_PTR;
    }

        enum Branch {
            RIGHT,
            LEFT,
        } flag;
        if (node->previous)
            flag = (node->previous->right == node) ? RIGHT : LEFT;
        else
            flag = LEFT;

        if (node->left) {
            if (flag == LEFT) {
                if (node->previous)
                    node->previous->left = node->left;
                else
                    tree->root = node->left;
            } else {
                if (node->previous)
                    node->previous->right = node->left;
                else
                    tree->root = node->left;
            }
            node->left->previous = node->previous;
        } else {
            if (flag == LEFT) {
                if (node->previous)
                    node->previous->left = node->right;
                else
                    tree->root = node->right;
            } else {
                if (node->previous)
                    node->previous->right = node->right;
                else
                    tree->root = node->right;
            }
            if (node->right)
                node->right->previous = node->previous;
        }

    free_node(node);
    return IT_IS_OK;
}

void swap_nodes(Tree * tree, Node * node1, Node * node2) {
    Node * ch1_1 = node1->left;
    Node * ch1_2 = node1->right;

    Node * ch2_1 = node2->left;
    Node * ch2_2 = node2->right;

    Node * p1 = node1->previous;
    Node * p2 = node2->previous;

    Node * tmp = NULL;

    // меняем местами левых детей
    if (ch1_1 == node2 || ch2_1 == node1) {
        if (node1 == ch2_1) {
            node2->left = ch1_1;
            node1->left = node2;
        } else {
            node1->left = ch2_1;
            node2->left = node1;
        }
    } else {
        node1->left = ch2_1;
        node2->left = ch1_1;
    }
    // меняем местами правых детей
    if (ch1_2 == node2 || ch2_2 == node1) {
        if (node1 == ch2_2) {
            node2->right = ch1_2;
            node1->right = node2;
        } else {
            node1->right = ch2_2;
            node2->right = node1;
        }
    } else {
        node1->right = ch2_2;
        node2->right = ch1_2;
    }
    // меняем местами родителей
    if (node1 == p2) {
        node1->previous = node2;
    } else {
        node1->previous = p2;
    }
    if (node2 == p1)
        node2->previous = node1;
    else
        node2->previous = p1;


    // меняем ссылки у родителей
    if (p1) {
        if (p1 != node2) {
            if (p1->left == node1) {
                p1->left = node2;
            } else {
                p1->right = node2;
            }
        }
    } else {
        tree->root = node2;
    }
    if (p2) {
        if (p2 != node1) {
            if (p2->left == node2) {
                p2->left = node1;
            } else {
                p2->right = node1;
            }
        }
    } else {
        tree->root = node1;
    }

    if (ch1_1)
        if (ch1_1 != node2)
            ch1_1->previous = node2;
    if (ch1_2)
        if (ch1_2 != node2)
            ch1_2->previous = node2;
    if (ch2_1)
        if (ch2_1 != node1)
            ch2_1->previous = node1;
    if (ch2_2)
        if (ch2_2 != node1)
            ch2_2->previous = node1;
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

    if (node->right && node->left) {
        if (min_node) {
            swap_nodes(tree, node, min_node);
            //delete_list_or_one_child_node(node);
        }
        else if (max_node) {
            swap_nodes(tree, node, max_node);
        }
    }
    /*
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
     */

    delete_list_or_one_child_node(tree, node);

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
                // fprintf(stderr, "There is no element with such key in this tree.\n");
                return NULL;
            }
            node = node->right;
        } else {
            if (node->left == NULL) {
                // fprintf(stderr, "There is no element with such key in this tree.\n");
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

size_t depth_of_tree(Node * node) {
    if (node == NULL)
        return 0;
    size_t left_depth = 1+depth_of_tree(node->left);
    size_t right_depth = 1+depth_of_tree(node->right);
    return (left_depth > right_depth) ? left_depth: right_depth;
}

Error recursion_print_BT_modified(Node* node, char ** offset) {
    if (offset == NULL || *offset == NULL)
        return NULL_PTR_IN_UNEXCITED_PLACE;

    size_t l = strlen(*offset);
    if (l>0 && (*offset)[l-1] != ' ' || (*offset)[0] == '\0') {
        printf("%s\n", *offset);
        printf("%s\\", *offset);
    }
    else {
        (*offset)[l-1] = '|';
        printf("%s\n", *offset);
        (*offset)[l-1] = ' ';
        printf("%s\\", *offset);
    }
    if (node)
        print_key(node->key);
    else
        printf("-\n");


    if (node == NULL || node->left == NULL && node->right == NULL)
        return IT_IS_OK;

    size_t len = strlen(*offset)+2;
    *offset = realloc(*offset, sizeof(size_t) * len);
    (*offset)[len-1] = '\0';
    (*offset)[len-2] = '|';

    recursion_print_BT_modified(node->left, offset);
    (*offset)[len-2] = ' ';
    recursion_print_BT_modified(node->right, offset);
    len--;
    *offset = realloc(*offset, sizeof(char) * len);
    (*offset)[len-1] = '\0';

    return IT_IS_OK;
}

Error print_BT_modified(const Tree * tree) {
    size_t depth = depth_of_tree(tree->root);
    char * offset = malloc(sizeof(char));
    offset[0] = '\0';
    recursion_print_BT_modified(tree->root, &offset);
    free(offset);
    return IT_IS_OK;
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

Error fill_tree_with_random_data(Tree * tree, size_t number, unsigned int min, unsigned int max, size_t key_size) {
    if (tree == NULL || min > max) {
        return WRONG_INPUT;
    }

    for (size_t i = 0; i < number; ++i) {
        KeyType * key = generate_key(key_size);
        InfoType * info = generate_info(min, max);
        if (add_el_into_BT(tree, key, info) != IT_IS_OK) {
            free_key(key);
            free_info(info);
        }
    }
    return IT_IS_OK;
}