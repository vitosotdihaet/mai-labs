#include <stdio.h>

#include "db.h"
#include "sample_db.h"


void print_usage() {
    printf(
        "Usage of program:\n"
        "\t-f\t Input file of database\n"
        "\t-p\t Parameters\n"
    );
}

void crash() {
    print_usage();
    exit(1);
}


int main(int argc, char const *agrv[]) {
    // if (argc < 2) {
    //     crash();
    // }

    create_sample_db();

    Database db;
    FILE *f = fopen("test.db4l", "rb");

    database_read(&db, f);
    database_print(db);

    fclose(f);
    return 0;
}