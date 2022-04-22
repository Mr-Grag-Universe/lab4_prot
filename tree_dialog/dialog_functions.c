//
// Created by Stephan on 18.04.2022.
//
#include <time.h>
#include "stdio.h"
#include "stdlib.h"
#include "sys/time.h"
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

Error print_tree_dialog(const Tree * tree) {

    return print_BT_modified(tree);//print_BT(tree);
}

Error get_tree_dialog(const Tree * tree) {
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

Error traversal_tree_dialog(const Tree* tree) {
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

Error find_min_dialog(const Tree * tree) {
    if (tree == NULL) {
        fprintf(stderr, "WARNING: This tree's pointer is NULL and there is no min or max element here.\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }

    Node * min = get_min_node(tree->root);
    return print_node(min);
}

Error find_max_dialog(const Tree * tree) {
    if (tree == NULL) {
        fprintf(stderr, "WARNING: This tree's pointer is NULL and there is no min or max element here.\n");
        return NULL_PTR_IN_UNEXCITED_PLACE;
    }

    Node * max = get_max_node(tree->root);
    return print_node(max);
}

Error timing_dialog() {
    srand(time(NULL));

    long double * table_of_results = malloc(sizeof(long double) * 100);

    for (int i = 0; i < 100; ++i) {
        size_t number_of_elements = 10000*(i+1);
        printf("number: %ld\n", number_of_elements);


        Node * node = NULL;
        Tree *tree = init_tree();
        if (tree == NULL) {
            fprintf(stderr, "timing allocing wrong!\n");
            return MEMORY_OVERFLOW;
        }
        printf("start filling\n");
        fill_tree_with_random_data(tree, number_of_elements, 0, 100, 5);
        printf("finish filling\n");

        /*
        // traversal time
        start = clock();
        TreeIteratorContainer * container = create_iterator(tree);
        finish = clock();
        traversal_time = (traversal_time + (double) (finish-start) / CLOCKS_PER_SEC) / 2;
        free_container(container);
         */

        long double search_time = 0;
        size_t number_of_checking = 10000;
        size_t * results = malloc(sizeof(size_t) * number_of_checking);

        for (int j = 0; j < number_of_checking; ++j) {
            // searching time
            KeyType *key = generate_key(5);

            struct timeval start;
            struct timeval finish;
            //printf("start find\n");
            gettimeofday(&start, NULL);
            node = get_node_from_BT(tree, key);
            gettimeofday(&finish, NULL);
            //print_node(node);

            results[j] = ((finish.tv_sec-start.tv_sec)*1000000 + (finish.tv_usec-start.tv_usec) );
            if (results[j] > 100000) {
                printf("throughout\n");
            }
            //search_time = (search_time + (finish.tv_sec-start.tv_sec)*1000 + (finish.tv_usec-start.tv_usec) )/ 2;
            //printf("%ld\n", search_time);
            //printf("finish find\n");
            free_key(key);
        }
        free_BT(tree);
        for (size_t j = 0; j < number_of_checking; ++j) {
            search_time = search_time + (double)results[j]/1000;// / 2;
        }
        search_time /= number_of_checking;
        free(results);
        table_of_results[i] = search_time;

        // printf("traversal time: %.20Lf\n", traversal_time);
        printf("search time %Lf\n", search_time);
    }

    for (size_t i = 0; i < 100; ++i) {
        printf("%ld: %Lf\n", (i+1)*10000, table_of_results[i]);
    }
    free(table_of_results);

    return IT_IS_OK;
}

Error random_dialog(Tree * tree) {
    fill_tree_with_random_data(tree, 10, 0, 100, 4);
    return IT_IS_OK;
}

Error read_tree_dialog(Tree ** tree) {
    printf("Do you really want to delete your current tree?\n");
    char * answer = get_line();
    if (!(!strcmp(answer, "y") || !strcmp(answer, "yes"))) {
        if (answer)
            free(answer);
        return IT_IS_OK;
    }
    free(answer);

    free_BT(*tree);

    *tree = read_tree("tree.txt");

    return IT_IS_OK;
}