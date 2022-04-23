//
// Created by Stephan on 17.04.2022.
//
#include "binary_tree.h"
#include "stdbool.h"
#include "stdlib.h"
#include "stdio.h"
#include "KGetLine.h"
#include "MyString.h"

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
    if (key == NULL || key->strKey == NULL) {
        printf("null\n");
        return false;
    }

    printf("strKey: %s\n", key->strKey);
    return true;
}

KeyType * enter_key() {
    KeyType * key = malloc(sizeof(KeyType));
    if (key == NULL) {
        fprintf(stderr, "Cannot alloc memory for new entered key!\n");
        exit(MEMORY_OVERFLOW);
    }

    key->strKey = get_line();
    if (key->strKey)
        key->keySize = strlen(key->strKey)+1;
    else {
        key->keySize = 0;
        fprintf(stderr, "null key has been entered.\n");
    }

    return key;
}

Error free_key(KeyType * key) {
    if (key == NULL) {
        fprintf(stderr, "Invalid free of null key.\n");
        return FREEING_OF_NULL_PTR;
    }
    if (key->strKey == NULL) {
        fprintf(stderr, "WARNING: key with null strKey was freed.\n");
        free(key);
        return IT_IS_OK;
    }

    free(key->strKey);
    key->strKey = NULL;

    free(key);
    key = NULL;

    return IT_IS_OK;
}

KeyType * generate_key(size_t key_size) {
    KeyType * key = malloc(sizeof(KeyType));

    key->strKey = generate_word(key_size);

    key->keySize = key_size;
    return key;
}

//=============INFO===========

InfoType * init_info() {
    InfoType * info = malloc(sizeof(InfoType));
    if (info == NULL) {
        fprintf(stderr, "there is no enough memory to alloc for info initialisation\n");
        exit(MEMORY_OVERFLOW);
    }

    info->val = 0;
    return info;
}

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

    printf("val: %u\n", info->val);
    return true;
}

InfoType * enter_info() {
    InfoType * info = malloc(sizeof(InfoType));
    if (info == NULL) {
        fprintf(stderr, "Cannot alloc memory for new entered info!\n");
        exit(MEMORY_OVERFLOW);
    }

    info->val = get_int();

    return info;
}

Error free_info(InfoType * info) {
    if (info == NULL) {
        fprintf(stderr, "Invalid free of null info.\n");
        return FREEING_OF_NULL_PTR;
    }

    free(info);
    info = NULL;

    return IT_IS_OK;
}

InfoType * generate_info(unsigned int min, unsigned int max) {
    InfoType * info = malloc(sizeof(InfoType));
    info->val = (rand() % (max-min)) + min;
    return info;
}