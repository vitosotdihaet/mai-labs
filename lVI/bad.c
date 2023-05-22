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

    int fields_num = 2;

    char *value = (char*) calloc(10, sizeof(char));
    char **values = (char**) calloc(fields_num, sizeof(char*));
    for (int i = 0; i < fields_num; ++i) {
        values[i] = (char*) calloc(10, sizeof(char));
    }

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
                value = argv[arg_ind + 1];
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

    char **fields = (char**) calloc(2, sizeof(char*));
    fields[0] = (char*) calloc(256, sizeof(char));
    fields[1] = (char*) calloc(256, sizeof(char));

    if (value[0] != '\0') {
        fields[0] = "Medal";
        fields[1] = "Points";

        values[0] = "1";
        char *temp = (char*) calloc(256, sizeof(char));
        temp[0] = 'l';
        temp[1] = 'e';
        strcat(temp, value);
        values[1] = temp;

        database_print_matching(db, fields, values, fields_num);
    } else {
        database_print(db);
    }


    fclose(f);

    return 0;
}