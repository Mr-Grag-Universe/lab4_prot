//
// Created by Stephan on 22.04.2022.
//
#include "gtest/gtest.h"
#include "stdlib.h"
#include "binary_tree.h"
#include "Errors.h"


TEST(all_tests, adding) {
    Tree * tree = init_tree();
    KeyType * key = generate_key(1);
    ASSERT_NE(key, nullptr);
    ASSERT_NE(key->strKey, nullptr);
    InfoType * info = generate_info(0, 100);
    ASSERT_NE(info, nullptr);

    Error report = add_el_into_BT(tree, key, info);

    ASSERT_NE(report, NULL_PTR_IN_UNEXCITED_PLACE);
    ASSERT_NE(report, MEMORY_OVERFLOW);

    Node * node = get_node_from_BT(tree, key);
    ASSERT_NE(node, nullptr);
    //ASSERT_TRUE(key_cmp(key, node->key) == 0);
    if (node->previous) {
        //ASSERT_TRUE(node->previous->left == node || node->previous->right == node);
    }
    if (node->left) {
        //ASSERT_TRUE(node->left->previous == node);
    }
    if (node->right) {
        //ASSERT_TRUE(node->right->previous == node);
    }
}