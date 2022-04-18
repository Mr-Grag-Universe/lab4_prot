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