/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "abb.h" /* TAD abb */


void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

abb abb_from_file(const char *filepath) {
    FILE *file = NULL;
    abb read_tree;

    read_tree = abb_empty();
    file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i = 0u;
    unsigned int size = 0u;
    int res = 0;
    res = fscanf(file, " %u ", &size);
    if (res != 1) {
        fprintf(stderr, "Invalid format.\n");
        exit(EXIT_FAILURE);
    }
    while (i < size) {
        abb_elem elem;
        res = fscanf(file," %d ", &(elem));
        if (res != 1) {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }
        read_tree = abb_add(read_tree, elem);

       ++i;
    }
    fclose(file);
    return read_tree;
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* parse the file to obtain an abb with the elements */
    abb tree = abb_from_file(filepath);



    /*dumping the tree*/
    abb_dump(tree);
    printf("\n");
    printf("raiz: %d\nminimo: %d\nmaximo: %d\nlength: %d\n", abb_root(tree),
           abb_min(tree),
           abb_max(tree),
           abb_length(tree));

    int opcion;
    printf("1)ADD | 2)Remove | 3)Salir:\n");
    scanf("%d", &opcion);
    while(opcion != 3) {
        if (opcion == 1) {
            int add;
            printf("Que elemento agregas?: ");
            scanf("%d", &add);
            tree = abb_add(tree, add);
        } else if (opcion == 2) {
            int del;
            printf("Que elemento removes?: ");
            scanf("%d", &del);
            tree = abb_remove(tree, del);
        }
        abb_dump(tree);
        printf("\n");
        printf("raiz: %d\nminimo: %d\nmaximo: %d\nlength: %d\n", abb_root(tree),
               abb_min(tree),
               abb_max(tree),
               abb_length(tree));

        printf("\n1)ADD | 2)Remove | 3)Salir:\n");
        scanf("%d", &opcion);
    }

    printf("Arbol final: \n");
    abb_dump(tree);
    printf("\n");
    printf("raiz: %d\nminimo: %d\nmaximo: %d\nlength: %d\n", abb_root(tree),
           abb_min(tree),
           abb_max(tree),
           abb_length(tree));

    tree = abb_destroy(tree);

    return (EXIT_SUCCESS);
}
