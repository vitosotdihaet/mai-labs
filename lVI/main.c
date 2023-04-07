#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "db.h"


void print_usage() {
    printf(
        "Usage of program:\n"
        "\tNecessary:\n"
        "\t\t-f [FILE]\t\t Filename of database that needs to be read\n"
        "\tUnnecessary:\n"
        "\t\t-p [FIELD] [MIN]\t Print all rows that have given field with minimum value\n"
    );
}

void crash() {
    print_usage();
    exit(1);
}


int main(int argc, char const *argv[]) {
    if (argc < 2) {
        crash();
    }

    char *filename = (char*) calloc(256, sizeof(char));

    int fields_num = (argc - 3)/3;

    char **fields = (char**) calloc(fields_num, sizeof(char*));
    for (int i = 0; i < fields_num; ++i) {
        fields[i] = (char*) calloc(10, sizeof(char));
    }

    char **values = (char**) calloc(fields_num, sizeof(char*));
    for (int i = 0; i < fields_num; ++i) {
        values[i] = (char*) calloc(10, sizeof(char));
    }

    int off = 0;
    for (int arg_ind = 1; arg_ind < argc; ++arg_ind) {
        // printf("param: %s\n", argv[arg_ind]);
        switch (argv[arg_ind][1]) {
            case 'f':
                if (arg_ind + 1 < argc) {
                    filename = argv[arg_ind + 1];
                    arg_ind++;
                }
                break;
            case 'p':
                if (arg_ind + 2 < argc) {
                    fields[off] = argv[arg_ind + 1];
                    values[off] = argv[arg_ind + 2];
                    off++;
                    arg_ind++;
                    arg_ind++;
                }
                break;
        }
    }

    if (*filename == NULL) {
        printf("No filename given!\n");
        crash();
    }

    Database db;
    FILE *f = fopen(filename, "rb");

    database_read(&db, f);

    database_print_matching(db, fields, values, fields_num);

    // printf("%s\n", filename);
    // printf("%s\n%d\n", field, maximal_value);

    fclose(f);
    return 0;
}