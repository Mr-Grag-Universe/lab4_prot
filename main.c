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
    menu_points[GET_EL] = "get an element";
    menu_points[PRINT_TREE] = "print tree";
    menu_points[DELETE_ALl] = "delete all";
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

bool execute_command(Tree * tree, Command command) {
    switch (command) {
        case EXIT: {
            printf("OK. Goodbye!\n");
            return true;
        }
        case ADD_EL: {
            add_tree_dialog(tree);
            return false;
        }
        case GET_EL: {
            return false;
        }
        case DELETE_EL: {
            delete_tree_dialog(tree);
            return false;
        }
        case PRINT_TREE: {
            print_tree_dialog(tree);
            return false;
        }
        case DELETE_ALl: {
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
        return GET_EL;
    else if (!strcmp(command, "add"))
        return ADD_EL;
    else if (!strcmp(command, "delete"))
        return DELETE_EL;
    else if (!strcmp(command, "print"))
        return PRINT_TREE;
    else if (!strcmp(command, "delete all"))
        return DELETE_ALl;
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


        finish = execute_command(tree, command_code);

        free(command);
    }
    free_BT(tree);
    free(menu);

    return 0;
}