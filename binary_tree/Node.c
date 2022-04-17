//
// Created by Stephan on 17.04.2022.
//
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "unistd.h"
#include "Errors.h"
#include "binary_tree.h"

Node * init_node() {
    Node * node = malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Cannot alloc memory in init node.\n");
        return NULL;
    }

    node->left = NULL;
    node->right = NULL;
    node->info = NULL;
    node->key = NULL;
    node->previous = NULL;

    return node;
}

InfoType * get_info_from_node(const Node * node) {
    if (node == NULL) {
        fprintf(stderr, "NULL node in get_info_from_node.\n");
        exit(NULL_PTR_IN_UNEXCITED_PLACE);
    }

    if (node->info == NULL) {
        fprintf(stderr, "WARNING: null info in node:\n");
        print_node(node);
        sleep(1);
    }
    if (node->key == NULL) {
        fprintf(stderr, "WARNING: null key in node:\n");
        print_node(node);
        sleep(1);
    }

    return node->info;
}

Node * get_max_node(const Node * node) {
    if (node == NULL)
        return NULL;

    Node * res = node;
    while (res->right) {
        res = res->right;
    }

    return res;
}

Node * get_min_node(const Node * node) {
    if (node == NULL)
        return NULL;

    Node * res = node;
    while (res->left) {
        res = res->left;
    }

    return res;
}

Error print_node(const Node * node) {
    if (node == NULL) {
        fprintf(stderr, "NULL node in get_info_from_node.\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }

    if (!print_key(node->key) || !print_info(node->info))
        return WRONG_INPUT;

    return IT_IS_OK;
}

Error free_node(Node * node) {
    if (node == NULL)
        return FREEING_OF_NULL_PTR;

    if (free_info(node->info) == FREEING_OF_NULL_PTR || free_key(node->key) == FREEING_OF_NULL_PTR) {
        return FREEING_OF_NULL_PTR;
    }

    return IT_IS_OK;
}