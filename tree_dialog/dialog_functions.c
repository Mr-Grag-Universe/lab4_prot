//
// Created by Stephan on 18.04.2022.
//
#include "stdio.h"
#include "Errors.h"
#include "binary_tree.h"
#include "KGetLine.h"
#include "MyString.h"

Error add_tree_dialog(Tree * tree) {
    printf("Enter your key: ");
    KeyType * key = enter_key();
    if (key == NULL) {
        fprintf(stderr, "Entered key is null!\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }

    printf("Enter your info: ");
    InfoType * info = enter_info();
    if (info == NULL) {
        fprintf(stderr, "Entered info is null!\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }

    return add_el_into_BT(tree, key, info);
}

Error delete_tree_dialog(Tree * tree) {
    printf("Enter your key: ");
    KeyType * key = enter_key();
    if (key == NULL) {
        fprintf(stderr, "Entered key is null!\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }

    Error report = delete_el_from_BT(tree, key);
    free_key(key);

    return report;
}

Error print_tree_dialog(Tree * tree) {
    return print_BT(tree);
}

Error get_tree_dialog(Tree * tree) {
    printf("Enter your key: ");
    KeyType * key = enter_key();
    if (key == NULL) {
        fprintf(stderr, "Entered key is null!\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }

    InfoType * info = get_info_from_BT(tree, key);
    free_key(key);

    if (!print_info(info) || !print_key(key))
        return WRONG_INPUT;

    return IT_IS_OK;
}

Error traversal_tree_dialog(Tree* tree) {
    TreeIteratorContainer * container = create_iterator(tree);
    if (container == NULL) {
        printf("this tree is empty or something came wrong!\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }

    for (size_t i = 0; i < container->number_of_elements; ++i) {
        print_node(container->iterator[i]);
    }

    free_container(container);
    return IT_IS_OK;
}

Error find_min_dialog(Tree * tree) {
    if (tree == NULL) {
        fprintf(stderr, "WARNING: This tree's pointer is NULL and there is no min or max element here.\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }

    Node * min = get_min_node(tree->root);
    return print_node(min);
}

Error find_max_dialog(Tree * tree) {
    if (tree == NULL) {
        fprintf(stderr, "WARNING: This tree's pointer is NULL and there is no min or max element here.\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }

    Node * max = get_max_node(tree->root);
    return print_node(max);
}