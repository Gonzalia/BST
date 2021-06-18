//
// Created by juampa on 17/6/21.
//
#include "util.h"

char* generateSpaces(int spaces) {
    char* str = calloc(spaces + 1, sizeof(char));
    memset(str, ' ', spaces);
    str[spaces] = '\0';
    return str;
}

void printAbbFormatted(abb abb, int spaces) {
    if(!abb_is_empty(abb)) {
        char* strSpaces = generateSpaces(spaces);
        printf("%s(+) ", strSpaces);
        printf(CYAN "%d" MAGENTA RESET "\n", abb->elem);

        if(!abb_is_empty(abb->left) || !abb_is_empty(abb->right)) {
            // printf("\n" BLUE "%s%s's childs\n" RESET,generateSpaces(spaces), abb->key);
            printf("%s- Left branch -\n", generateSpaces(spaces + 4));
            printAbbFormatted(abb->left, spaces + 4);
            printf("%s- Right branch -\n", generateSpaces(spaces + 4));
            printAbbFormatted(abb->right, spaces + 4);
        }
    }
    else {
        printf("%s(+) Empty branch\n", generateSpaces(spaces + 4));
    }
}

/*
 * @toString: function takes abb->elem and returns a string representation of it
 * */
void printAbb(abb abb) {
    printAbbFormatted(abb, 0);
}