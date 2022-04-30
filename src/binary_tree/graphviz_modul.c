//
// Created by Stephan on 29.04.2022.
//
#include <stdlib.h>
#include "stdio.h"
#include "string.h"
#include "Errors.h"
#include "FGetLine.h"
#include "tree_dialog.h"
#include "SortsSearch.h"

const char l1[] = "digraph {\n";
const char l2[] = "\tnode [style=\"filled\", color=\"black\", fillcolor=\"skyblue\"];\n";
const char l3[] = " [label = \"";

Error init_graph() {
    FILE * file = fopen("test_g.gv", "w");
    fwrite(l1, 1, strlen(l1), file);
    fwrite(l2, 1, strlen(l2), file);
    fwrite("}", 1, 1, file);

    fclose(file);

    return IT_IS_OK;
}

char * create_name(int ind) {
    char * name = calloc(1, sizeof(char) * 10);
    // itoa(ind, name+1, 10);
    sprintf(name+2, "%u", ind);
    name[0] = '\t';
    name[1] = 'a';
    return name;
}

int comp(const void * _node1, const void * _node2) {
    KeyType * key1 = ((Node*) _node1)->key;
    KeyType * key2 = ((Node*) _node2)->key;
    return -key_cmp(key1, key2);
}

Error update_graph(Tree * tree) {
    if (tree == NULL)
        return NULL_PTR_IN_UNEXCITED_PLACE;

    FILE * file = fopen("test_g.gv", "r+");
    if (file == NULL) {
        init_graph();
        file = fopen("test_g.gv", "r+");
    }

    /*
    char ** lines = f_get_lines("test_g.gv");
    if (lines == NULL)
        return NULL_PTR_IN_UNEXCITED_PLACE;

    int i = 0;
    while (lines[i] && strcmp(lines[i], "}") != 0) { i++; }
    int len = 0;
    while (lines[len]) { len++; }
    if (lines[i] == NULL) {
        fprintf(stderr, "there is no \'}\' in .gv file\n");
        exit(NULL_PTR_IN_UNEXCITED_PLACE);
    }

    i--;
    lines = realloc(lines, sizeof(char *) * (len+2));
    memmove(lines+i+1, lines+i, sizeof(char *) * 2);

    char name[10];
    itoa(len/2, name, 10);
    size_t name_len = strlen(name);

    lines[i] = malloc(sizeof(char) * ( + 1));
     */

    TreeIteratorContainer * container = create_iterator(tree);
    size_t number = container->number_of_elements;

    fwrite(l1, 1, strlen(l1), file);
    fwrite(l2, 1, strlen(l2), file);

    for (int i = 0; i < number; ++i) {
        char * name = create_name(i);
        size_t name_len = strlen(name);

        fwrite(name, 1, name_len, file);
        fwrite(l3, 1, strlen(l3), file);
        char data[50];
        sprintf(data, "%u", container->iterator[i]->info->val);
        // itoa((int) container->iterator[i]->info->val, data, 10);
        fwrite(data, 1, strlen(data), file);
        fwrite("\"];\n", 4, sizeof(char), file);
    }

    fwrite("\n", 1, 1, file);

    for (int i = 0; i < number; ++i) {
        char * name = create_name(i);
        size_t name_len = strlen(name);

        Node * node = container->iterator[i];
        size_t ind1 = -1;
        size_t ind2 = -1;
        if (node->left)
            ind1 = binarySearch(container->iterator, node->left, number, sizeof(Node*), comp);
        if (node->right)
            ind2 = binarySearch(container->iterator, node->right, number, sizeof(Node*), comp);

        if (ind1 != -1) {
            char * name1 = create_name((int) ind1);
            size_t name_len1 = strlen(name1);

            fwrite(name, 1, name_len, file);
            fwrite(" -> ", 1, 4, file);
            fwrite(name1, 1, name_len1, file);
            fwrite(";\n", 1, 2, file);
            free(name1);
        }

        if (ind2 != -1) {
            char * name2 = create_name((int) ind2);
            size_t name_len2 = strlen(name2);

            fwrite(name, 1, name_len, file);
            fwrite(" -> ", 1, 4, file);
            fwrite(name2, 1, name_len2, file);
            fwrite(";\n", 1, 2, file);
            free(name2);
        }
    }

    fwrite("}", 1, 1, file);

    fclose(file);

    return IT_IS_OK;
}