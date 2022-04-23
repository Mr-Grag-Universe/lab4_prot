//
// Created by Stephan on 18.04.2022.
//

#ifndef LAB4_PROT_TREE_DIALOG_H
#define LAB4_PROT_TREE_DIALOG_H
#include "Errors.h"

Error add_tree_dialog(Tree * tree);
Error print_tree_dialog(Tree * tree);
Error delete_tree_dialog(Tree * tree);
Error get_tree_dialog(const Tree * tree);
Error traversal_tree_dialog(const Tree* tree);
Error find_min_dialog(const Tree * tree);
Error find_max_dialog(const Tree * tree);
Error timing_dialog();
Error random_dialog(Tree * tree);
Error read_tree_dialog(Tree ** tree);
#endif //LAB4_PROT_TREE_DIALOG_H
