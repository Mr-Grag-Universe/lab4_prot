//
// Created by Stephan on 22.04.2022.
//
#include "Errors.h"
#include "binary_tree.h"
#include "stdlib.h"
#include "stdio.h"
#include "FGetLine.h"
#include "errno.h"

KeyType * read_key(FILE * file, long offset) {
    if (file == NULL)
        return NULL;

    KeyType * key = init_key();
    if (key == NULL)
        return NULL;

    key->strKey = f_get_line(file, offset);
    return key;
}

InfoType * read_info(FILE * file, long offset) {
    if (file == NULL)
        return NULL;

    InfoType * info = init_info();

    char * line = f_get_line(file, offset);
    if (line == NULL || line[0] == '\0') {
        fprintf(stderr, "cannot read any line from this file.\n");
        if (line)
            free(line);
        return info;
    }

    long x = strtol(line, NULL, 10);
    free(line);
    if (errno == ERANGE) {
        fprintf(stderr, "not correct data in file!\ninfo val was turned to the 0\n");
        info->val = 0;
        return info;
    }

    info->val = x;

    return info;
}

Tree * read_tree(char * name_of_file) {
    if (name_of_file == NULL || name_of_file[0] == '\0')
        return NULL;

    FILE * file = fopen(name_of_file, "r");
    if (file == NULL) {
        return NULL;
    }

    Tree * tree = init_tree();

    while (feof(file) != EOF) {
        KeyType * key = read_key(file, ftell(file));
        InfoType * info = read_info(file, ftell(file));
        if (!(key && key->strKey && info) || add_el_into_BT(tree, key, info) != IT_IS_OK) {
            if (key)
                free_key(key);
            if (info)
                free_info(info);
            break;
        }
    }
    fclose(file);

    return tree;
}