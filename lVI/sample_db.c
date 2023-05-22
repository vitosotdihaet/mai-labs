#include <stdio.h>

#include "db.h"

int create_sample_db() {
    Database db;
    database_init(&db, 30);
    database_add(&db, "zniatos",     "KM",     0, 5,    1, 100, 0);
    database_add(&db, "xzzniascasw", "mv",     0, 5,    1, 0,   1);
    database_add(&db, "asczniaw",    "xasd",   1, 2,    0, 130, 1);
    database_add(&db, "ascznczxciw", "Kasd",   1, 5,    0, 100, 1);
    database_add(&db, "asazniaxw",   "sd",     0, 5,    0, 10,  0);
    database_add(&db, "aszniaxw",    "ab",     1, 10,   1, 60,  0);
    database_add(&db, "xasczniaw",   "as",     0, 3,    0, 135, 1);
    database_add(&db, "azniaasw",    "d",      1, 134,  1, 2,   0);
    database_add(&db, "bniaxs",      "KM",     0, 5,    1, 100, 0);
    database_add(&db, "bzznxscasw",  "mv",     0, 5,    1, 0,   1);
    database_add(&db, "bsczxaw",     "xasd",   1, 2,    0, 130, 1);
    database_add(&db, "bsczxzxciw",  "Kasd",   1, 5,    0, 100, 1);
    database_add(&db, "bsazxaxw",    "sd",     0, 5,    0, 10,  1);
    database_add(&db, "bsznxxw",     "ab",     1, 10,   1, 12,  0);
    database_add(&db, "bascxiaw",    "as",     1, 3,    1, 175, 1);
    database_add(&db, "bznixsw",     "d",      1, 14,   0, 2,   0);
    database_add(&db, "aaxw",        "aaab",   1, 10,   1, 60,  0);
    database_add(&db, "xniaw",       "aaas",   0, 3,    0, 135, 1);
    database_add(&db, "aasw",        "aaa",    1, 134,  1, 2,   0);
    database_add(&db, "bs",          "aaaM",   0, 77,   1, 100, 0);
    database_add(&db, "bscasw",      "aaav",   0, 5,    1, 0,   1);
    database_add(&db, "baw",         "aaaasd", 1, 228,  0, 50,  1);
    database_add(&db, "bzxciw",      "aaaasd", 1, 1337, 0, 100, 1);
    database_add(&db, "baxw",        "aaad",   0, 5,    0, 10,  0);
    database_add(&db, "bxw",         "aaab",   1, 10,   1, 13,  0);
    database_add(&db, "biaw",        "aaas",   0, 3,    1, 175, 0);
    database_add(&db, "bsw",         "aaa",    1, 14,   0, 2,   0);

    // database_print(db);
    FILE *fw = fopen("test.db4l", "wb");
    database_dump(db, fw);
    fclose(fw);


    // Database dbr;
    // FILE *fr = fopen("test.db4l", "rb");
    // database_read(&dbr, fr);
    // database_print(dbr);
    // fclose(fr);


    return 0;
}