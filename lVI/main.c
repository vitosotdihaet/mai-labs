#include "db.h"

#define DB_ROWS 50
#define DB_COLS 7

int main() {
    Database db;
    database_init(&db);
    database_add(&db);
    database_print(db);

    return 0;
}