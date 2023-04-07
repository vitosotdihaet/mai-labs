#include <stdio.h>
#include <stdlib.h>

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

    char *field = (char*) calloc(10, sizeof(char));
    char *minimal_value_string = (char*) calloc(10, sizeof(char));
    short minimal_value = 0;

    for (int arg_ind = 1; arg_ind < argc; ++arg_ind) {
        switch (argv[arg_ind][1]) {
            case 'f':
                if (arg_ind + 1 < argc) {
                    filename = argv[arg_ind + 1];
                }
                break;
            case 'p':
                if (arg_ind + 2 < argc) {
                    field = argv[arg_ind + 1];
                    minimal_value_string = argv[arg_ind + 2];
                }
                break;
        }
        // printf("param: %s\n", argv[arg_ind]);
    }

    if (*filename == NULL) {
        printf("No filename given!\n");
        crash();
    }

    minimal_value = (short) atoi(minimal_value_string);

    // printf("%s\n", filename);
    // printf("%s\n%d\n", field, minimal_value);

    Database db;
    FILE *f = fopen(filename, "rb");

    database_read(&db, f);
    // database_print(db);
    database_print_all_min(db, field, minimal_value);

    fclose(f);
    return 0;
}