#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stdbool.h"
#include "KGetLine.h"
#include "time.h"
#include "MyString.h"
#include "commands.h"
#include "Errors.h"
#include "binary_tree.h"
#include "tree_dialog.h"

void clrscr(){
    system("@cls||clear");
}

char ** init_menu_points() {
    char ** menu_points = malloc(sizeof(char*) * (UNKNOWN_COMMAND));
    menu_points[EXIT] = "exit";
    menu_points[ADD_EL] = "add a new element";
    menu_points[DELETE_EL] = "delete an element";
    menu_points[FIND_EL] = "find an element";
    menu_points[PRINT_TREE] = "print tree";
    menu_points[DELETE_ALl] = "delete all";
    menu_points[TRAVERSAL] = "tree traversal";
    menu_points[FIND_MIN_ELEMENT] = "find min element";
    menu_points[FIND_MAX_ELEMENT] = "find max element";
    menu_points[TIMING] = "check out time";// of traversal and searching in BT";
    menu_points[RANDOM_GENERATE] = "generate random tree data";
    menu_points[READ_TREE] = "read tree from file";
    return menu_points;
}

void print_menu(char ** menu) {
    printf("This is menu:\n");
    for (int i = 0; i < UNKNOWN_COMMAND; ++i) {
        printf("%d) %s\n", i, menu[i]);
    }
}

bool check_command(char * command) {

    return true;
}

bool execute_command(Tree ** tree, Command command) {
    switch (command) {
        case EXIT: {
            printf("OK. Goodbye!\n");
            return true;
        }
        case ADD_EL: {
            add_tree_dialog(*tree);
            return false;
        }
        case FIND_EL: {
            if (get_tree_dialog(*tree) != IT_IS_OK)
                printf("Wrong input or something else.\n");
            return false;
        }
        case DELETE_EL: {
            delete_tree_dialog(*tree);
            return false;
        }
        case PRINT_TREE: {
            print_tree_dialog(*tree);
            return false;
        }
        case DELETE_ALl: {
            free_BT(*tree);
            *tree = init_tree();
            return false;
        }
        case TRAVERSAL: {
            traversal_tree_dialog(*tree);
            char * answer = get_line();
            free(answer);
            return false;
        }
        case FIND_MIN_ELEMENT: {
            find_min_dialog(*tree);
            return false;
        }
        case FIND_MAX_ELEMENT: {
            find_max_dialog(*tree);
            return false;
        }
        case TIMING: {
            timing_dialog();
            return false;
        }
        case RANDOM_GENERATE: {
            random_dialog(*tree);
            return false;
        }
        case READ_TREE: {
            read_tree_dialog(tree);
            return false;
        }
        default: {
            printf("Your command is wrong!\n");
            return false;
        }
    }
    return false;
}

Command get_command_code(char * command) {
    if (is_digit(command)) {
        long int x = strtol(command, NULL, 10);
        if (x < 0 || x > UNKNOWN_COMMAND)
            return UNKNOWN_COMMAND;
        return x;
    }

    if (!strcmp(command, "exit"))
        return EXIT;
    else if (!strcmp(command, "get"))
        return FIND_EL;
    else if (!strcmp(command, "add"))
        return ADD_EL;
    else if (!strcmp(command, "delete"))
        return DELETE_EL;
    else if (!strcmp(command, "print"))
        return PRINT_TREE;
    else if (!strcmp(command, "delete all"))
        return DELETE_ALl;
    else if (!strcmp(command, "traversal"))
        return TRAVERSAL;
    else if (!strcmp(command, "min"))
        return FIND_MIN_ELEMENT;
    else if (!strcmp(command, "max"))
        return FIND_MAX_ELEMENT;
    else if (!strcmp(command, "time"))
        return TIMING;
    else if (!strcmp(command, "read"))
        return READ_TREE;
    else return UNKNOWN_COMMAND;
}

Tree * start_session() {
    Tree * tree = init_tree();
    return tree;
}

int main() {
    printf("Info: %ld, Node: %ld\n", sizeof(InfoType), sizeof(Node));
    printf("Tree: %ld\n", sizeof(Tree));
    srand(time(NULL));
    bool finish = false;
    char ** menu = init_menu_points();

    Tree * tree = start_session();
    if (tree == NULL) {
        fprintf(stderr, "tree is NULL.\nSomething came wrong.\nCheck creation or initial data\n");
        exit(NULL_PTR_IN_UNEXCITED_PLACE);
    }

    number_of_words_in_file();

    while (!finish) {
        /// clrscr();
        print_menu(menu);

        char * command = get_line();
        if (command[0] == '\0') {
            free(command);
            continue;
        }
        //delete_double_spaces(&command);

        if (check_command(command) == false) {
            printf("Your command is wrong.");
            free(command);
            continue;
        }

        Command command_code = get_command_code(command);

        finish = execute_command(&tree, command_code);

        free(command);
    }
    free_BT(tree);
    free(menu);

    return 0;
}