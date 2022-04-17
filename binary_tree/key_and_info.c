//
// Created by Stephan on 17.04.2022.
//
#include "binary_tree.h"
#include "stdbool.h"
#include "stdlib.h"
#include "stdio.h"

//===============KEY==============

KeyType * init_key() {
    KeyType * key = malloc(sizeof(KeyType));
    if (key == NULL) {
        fprintf(stderr, "Cannot alloc memory in init key.\n");
        return NULL;
    }

    key->strKey = NULL;
    key->keySize = 0;

    return key;
}

int key_cmp(KeyType * key1, KeyType * key2) {
    return strcmp(key1->strKey, key2->strKey);
}

/// copy src key to key                                     \n
/// free strKey in key if it's not NULL                     \n
/// return false if there is NULL and true in another case  \n
bool copy_key(KeyType * key, KeyType * src) {
    if (key == NULL || src == NULL)
        return false;

    if (key->strKey)
        free(key->strKey);

    key->strKey = malloc(sizeof(char) * src->keySize);
    memmove(key->strKey, src->strKey, src->keySize);

    key->keySize = src->keySize;

    return true;
}

bool print_key(KeyType * key) {
    if (key == NULL || key->strKey) {
        printf("null\n");
        return false;
    }

    printf("size: %ld\nstrKey: %s\n", key->keySize, key->strKey);
    return true;
}

Error free_key(KeyType * key) {
    if (key == NULL) {
        fprintf(stderr, "Invalid free of null key.\n");
        return FREEING_OF_NULL_PTR;
    }
    if (key->strKey == NULL) {
        fprintf(stderr, "WARNING: key with null strKey was freed.\n");
        return IT_IS_OK;
    }

    free(key->strKey);
    return IT_IS_OK;
}

//=============INFO===========

bool copy_info(InfoType * info, InfoType * src) {
    if (info == NULL || src == NULL)
        return false;

    info->val = src->val;
    return true;
}

bool print_info(InfoType * info) {
    if (info == NULL) {
        printf("null\n");
        return false;
    }

    printf("val: %ud\n", info->val);
    return true;
}

Error free_info(InfoType * info) {
    if (info == NULL) {
        fprintf(stderr, "Invalid free of null info.\n");
        return FREEING_OF_NULL_PTR;
    }

    free(info);
    return IT_IS_OK;
}